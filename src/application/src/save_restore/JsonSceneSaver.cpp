#include "save_restore/JsonSceneSaver.hpp"
#include "save_restore/JsonStrings.hpp"

#include "managers/ResourceManager.hpp"
#include "managers/MaterialsManager.hpp"

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

void JsonSceneSaver::save(std::ostream& _stream, const jl::Scene& _scene)
{
	Json::Value root;

	root[k_materials] = saveMaterials();
	root[k_scene] = saveScene(_scene);

	_stream << root;
}

//-----------------------------------------------------------------------------

Json::Value JsonSceneSaver::saveMaterials()
{
	Json::Value result;

	MaterialsManager::getInstance().forEachMaterial([&result](const std::string& _name, jl::Material& _material)
	{
		if (_name == "RoomMaterial")
			return;

		Json::Value material = saveMaterial(_material);
		material[k_name] = _name;
		result.append(std::move(material));
	});

	return result;
}

//-----------------------------------------------------------------------------

Json::Value JsonSceneSaver::saveMaterial(const jl::Material& _material)
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

Json::Value JsonSceneSaver::saveScene(const jl::Scene& _scene)
{
	Json::Value objects;
	_scene.forEachObject([&objects](const jl::Object& _object)
	{
		objects.append(saveObject(_object));
	});

	Json::Value result;
	result[k_lights] = saveLights(_scene.getLightsHolder());
	result[k_objects] = std::move(objects);

	return result;
}

//-----------------------------------------------------------------------------

Json::Value JsonSceneSaver::saveObject(const jl::Object& _object)
{
	Json::Value result;

	result[k_name]		= _object.getName();

	result[k_position]	= details::vec3ToJson(_object.getPosition());
	result[k_rotation]	= details::vec3ToJson(_object.getRotation());
	result[k_scale]		= details::vec3ToJson(_object.getScale());

	if (const jl::Model* model = _object.getModel())
	{
		result[k_model] = ResourceManager::getInstance().findSourceFile(*model);
	}
	if (const jl::Material* material = _object.getMaterial())
	{
		result[k_material] = MaterialsManager::getInstance().findMaterialName(*material);
	}

	return result;
}

//-----------------------------------------------------------------------------

Json::Value JsonSceneSaver::saveLights(const jl::LightsHolder& _lightsHolder)
{
	Json::Value result;

	{
		const std::vector<glm::vec4>& colors = _lightsHolder.getPointLightsColors();
		const std::vector<glm::vec3>& positions = _lightsHolder.getPointLightsPositions();
		ASSERT(colors.size() == positions.size());
		if (colors.size() == positions.size())
		{
			result[k_pointLights] = savePointLights(colors, positions);
		}
	}
	{
		const std::vector<glm::vec4>& colors = _lightsHolder.getDirectionalLightsColors();
		const std::vector<glm::vec3>& directions = _lightsHolder.getDirectionalLightsDirections();
		ASSERT(colors.size() == directions.size());
		if (colors.size() == directions.size())
		{
			result[k_directionalLights] = savePointLights(colors, directions);
		}
	}
	{
		const jl::AmbientLightData data = _lightsHolder.getAmbientLightData();

		Json::Value ambientLightJson;
		ambientLightJson[k_color] = details::vec4ToJson(data.color);
		ambientLightJson[k_weight] = data.weight;
		result[k_ambientLight] = std::move(ambientLightJson);
	}

	return result;
}

//-----------------------------------------------------------------------------

Json::Value JsonSceneSaver::savePointLights(const std::vector<glm::vec4>& colors, const std::vector<glm::vec3>& positions)
{
	Json::Value result;

	for (size_t i = 0, size = colors.size(); i < size; ++i)
	{
		Json::Value lightData;
		lightData[k_color] = details::vec4ToJson(colors[i]);
		lightData[k_position] = details::vec3ToJson(positions[i]);
		result.append(std::move(lightData));
	}

	return result;
}

//-----------------------------------------------------------------------------

Json::Value JsonSceneSaver::saveDirectionalLights(const std::vector<glm::vec4>& colors, const std::vector<glm::vec3>& directions)
{
	Json::Value result;

	for (size_t i = 0, size = colors.size(); i < size; ++i)
	{
		Json::Value lightData;
		lightData[k_color] = details::vec4ToJson(colors[i]);
		lightData[k_direction] = details::vec3ToJson(directions[i]);
		result.append(std::move(lightData));
	}

	return result;
}

//-----------------------------------------------------------------------------
