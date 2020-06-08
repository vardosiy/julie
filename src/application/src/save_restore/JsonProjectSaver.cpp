#include "save_restore/JsonProjectSaver.hpp"
#include "save_restore/JsonStrings.hpp"

#include "data/SceneWrapper.hpp"
#include "data/ObjectWrapper.hpp"

#include "renderer/managers/ResourceManager.hpp"
#include "renderer/managers/MaterialsManager.hpp"

#include "renderer/Mesh.hpp"
#include "renderer/Model.hpp"
#include "renderer/Material.hpp"
#include "renderer/UniformType.hpp"

#include "renderer/scene/Scene.hpp"
#include "renderer/scene/Object.hpp"
#include "renderer/scene/lights/LightsHolder.hpp"

#include "utils/Utils.hpp"

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

Json::Value vec2ToJson(const glm::vec2& _val) noexcept
{
	Json::Value result;

	result.append(_val.x);
	result.append(_val.y);

	return result;
}

//-----------------------------------------------------------------------------

Json::Value vec3ToJson(const glm::vec3& _val) noexcept
{
	Json::Value result;

	result.append(_val.x);
	result.append(_val.y);
	result.append(_val.z);

	return result;
}

//-----------------------------------------------------------------------------

Json::Value vec4ToJson(const glm::vec4& _val) noexcept
{
	Json::Value result;

	result.append(_val.x);
	result.append(_val.y);
	result.append(_val.z);
	result.append(_val.w);

	return result;
}

//-----------------------------------------------------------------------------

class PropertyValueSaver
{
public:
	Json::Value operator() (float _val)				{ return save(jl::UniformType::Float,	_val); }
	Json::Value operator() (int _val)				{ return save(jl::UniformType::Int,		_val); }
	Json::Value operator() (const glm::vec2& _val)	{ return save(jl::UniformType::Vec2,	vec2ToJson(_val)); }
	Json::Value operator() (const glm::vec3& _val)	{ return save(jl::UniformType::Vec3,	vec3ToJson(_val)); }
	Json::Value operator() (const glm::vec4& _val)	{ return save(jl::UniformType::Vec4,	vec4ToJson(_val)); }

	Json::Value operator() (const jl::Texture* _val)
	{
		return save(jl::UniformType::Texture2D, ResourceManager::getInstance().findSourceFile(*_val));
	}

	Json::Value operator() (const jl::CubeTexture* _val)
	{
		return save(jl::UniformType::CubeTexture, ResourceManager::getInstance().findSourceFile(*_val));
	}

private:
	Json::Value save(jl::UniformType _type, Json::Value&& _val)
	{
		const std::string_view typeStr = utils::toString(_type);

		Json::Value result;
		result[k_type] = Json::Value(typeStr.data(), typeStr.data() + typeStr.size());
		result[k_value] = std::move(_val);
		return result;
	}
};

//-----------------------------------------------------------------------------

} // namespace details

//-----------------------------------------------------------------------------

void JsonProjectSaver::save(std::ostream& _stream, const SceneWrapper& _sceneWrapper)
{
	Json::Value root;

	root[k_materials] = saveMaterials();
	root[k_scene] = saveScene(_sceneWrapper);

	_stream << root;
}

//-----------------------------------------------------------------------------

Json::Value JsonProjectSaver::saveMaterials()
{
	Json::Value result;

	const jl::Material& defaultMaterial = MaterialsManager::getInstance().getDefaultMaterial();
	MaterialsManager::getInstance().forEachMaterial([&result, &defaultMaterial](const std::string& _name, const jl::Material& _material)
	{
		if (&_material == &defaultMaterial)
		{
			return;
		}

		Json::Value material = saveMaterial(_material);
		material[k_name] = _name;
		result.append(std::move(material));
	});

	return result;
}

//-----------------------------------------------------------------------------

Json::Value JsonProjectSaver::saveMaterial(const jl::Material& _material)
{
	Json::Value result;

	if (const jl::Shader* shader = _material.getShader())
	{
		result[k_shader] = ResourceManager::getInstance().findSourceFile(*shader);
	}

	Json::Value properties;
	for (const auto& property : _material.getProperties())
	{
		Json::Value data = std::visit(details::PropertyValueSaver(), property.value);
		data[k_name] = property.name;
		properties.append(std::move(data));
	}

	result[k_properties] = std::move(properties);

	return result;
}

//-----------------------------------------------------------------------------

Json::Value JsonProjectSaver::saveScene(const SceneWrapper& _sceneWrapper)
{
	Json::Value objects;
	_sceneWrapper.forEachObject([&objects](const ObjectWrapper& _objWrapper)
	{
		objects.append(saveObject(_objWrapper));
	});

	Json::Value result;
	result[k_lights] = saveLights(_sceneWrapper.getLightsHolder());
	result[k_objects] = std::move(objects);

	return result;
}

//-----------------------------------------------------------------------------

Json::Value JsonProjectSaver::saveObject(const ObjectWrapper& _objWrapper)
{
	Json::Value result;

	result[k_name]		= _objWrapper.getName();

	result[k_position]	= details::vec3ToJson(_objWrapper.getPosition());
	result[k_rotation]	= details::vec3ToJson(_objWrapper.getRotation());
	result[k_size]		= details::vec3ToJson(_objWrapper.getSize());

	if (const jl::Model* model = _objWrapper.getModel())
	{
		result[k_model] = saveModel(*model);
	}

	return result;
}

//-----------------------------------------------------------------------------

Json::Value JsonProjectSaver::saveModel(const jl::Model& _model)
{
	Json::Value meshMaterials;

	const jl::u32 meshesCount = _model.getMeshesCount();
	for (jl::u32 i = 0; i < meshesCount; ++i)
	{
		const jl::Mesh& mesh = _model.getMesh(i);

		if (const jl::Material* material = mesh.getMaterial())
		{
			const std::string& materialName = MaterialsManager::getInstance().findMaterialName(*material);
			meshMaterials.append(materialName);
		}
		else
		{
			meshMaterials.append("");
		}
	}

	Json::Value result;
	result[k_path] = ResourceManager::getInstance().findSourceFile(_model);
	result[k_meshMaterials] = std::move(meshMaterials);
	return result;
}

//-----------------------------------------------------------------------------

Json::Value JsonProjectSaver::saveLights(const jl::LightsHolder& _lightsHolder)
{
	Json::Value result;

	{
		const std::vector<glm::vec3>& colors = _lightsHolder.getPointLightsColors();
		const std::vector<glm::vec3>& positions = _lightsHolder.getPointLightsPositions();
		ASSERT(colors.size() == positions.size());
		if (colors.size() == positions.size())
		{
			result[k_pointLights] = savePointLights(colors, positions);
		}
	}
	{
		const std::vector<glm::vec3>& colors = _lightsHolder.getDirectionalLightsColors();
		const std::vector<glm::vec3>& directions = _lightsHolder.getDirectionalLightsDirections();
		ASSERT(colors.size() == directions.size());
		if (colors.size() == directions.size())
		{
			result[k_directionalLights] = saveDirectionalLights(colors, directions);
		}
	}
	{
		const jl::AmbientLightData data = _lightsHolder.getAmbientLightData();

		Json::Value ambientLightJson;
		ambientLightJson[k_color] = details::vec3ToJson(data.color);
		ambientLightJson[k_weight] = data.weight;
		result[k_ambientLight] = std::move(ambientLightJson);
	}

	return result;
}

//-----------------------------------------------------------------------------

Json::Value JsonProjectSaver::savePointLights(const std::vector<glm::vec3>& colors, const std::vector<glm::vec3>& positions)
{
	Json::Value result;

	for (size_t i = 0, size = colors.size(); i < size; ++i)
	{
		Json::Value lightData;
		lightData[k_color] = details::vec3ToJson(colors[i]);
		lightData[k_position] = details::vec3ToJson(positions[i]);
		result.append(std::move(lightData));
	}

	return result;
}

//-----------------------------------------------------------------------------

Json::Value JsonProjectSaver::saveDirectionalLights(const std::vector<glm::vec3>& colors, const std::vector<glm::vec3>& directions)
{
	Json::Value result;

	for (size_t i = 0, size = colors.size(); i < size; ++i)
	{
		Json::Value lightData;
		lightData[k_color] = details::vec3ToJson(colors[i]);
		lightData[k_direction] = details::vec3ToJson(directions[i]);
		result.append(std::move(lightData));
	}

	return result;
}

//-----------------------------------------------------------------------------
