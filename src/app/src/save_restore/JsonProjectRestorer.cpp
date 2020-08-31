#include "save_restore/JsonProjectRestorer.hpp"
#include "save_restore/JsonStrings.hpp"

#include "data/SceneWrapper.hpp"
#include "data/ObjectWrapper.hpp"

#include "julie/managers/ResourceManager.hpp"
#include "julie/managers/MaterialsManager.hpp"

#include "julie/Mesh.hpp"
#include "julie/Model.hpp"
#include "julie/Material.hpp"
#include "julie/UniformType.hpp"

#include "julie/scene/Scene.hpp"
#include "julie/scene/Object.hpp"
#include "julie/scene/lights/LightsHolder.hpp"

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

inline glm::vec2 jsonToVec2(const Json::Value& _val) noexcept
{
	if (_val.isArray() && _val.size() >= 2)
	{
		return glm::vec2(_val[0].asFloat(), _val[1].asFloat());
	}
	return glm::vec2(0.0f);
}

inline glm::vec3 jsonToVec3(const Json::Value& _val) noexcept
{
	if (_val.isArray() && _val.size() >= 3)
	{
		return glm::vec3(_val[0].asFloat(), _val[1].asFloat(), _val[2].asFloat());
	}
	return glm::vec3(0.0f);
}

inline glm::vec4 jsonToVec4(const Json::Value& _val) noexcept
{
	if (_val.isArray() && _val.size() >= 4)
	{
		return glm::vec4(_val[0].asFloat(), _val[1].asFloat(), _val[2].asFloat(), _val[3].asFloat());
	}
	return glm::vec4(0.0f);
}

//-----------------------------------------------------------------------------

} // namespace details

//-----------------------------------------------------------------------------

JsonProjectRestorer::JsonProjectRestorer(std::istream& _stream)
{
	Json::Value root;
	_stream >> root;

	restoreMaterials(root[k_materials]);
	restoreScene(root[k_scene]);
}

//-----------------------------------------------------------------------------

std::unique_ptr<SceneWrapper> JsonProjectRestorer::extractScene()
{
	return std::move(m_sceneWrapper);
}

//-----------------------------------------------------------------------------

void JsonProjectRestorer::restoreMaterials(const Json::Value& _json)
{
	for (const Json::Value& value : _json)
	{
		const std::string name = value[k_name].asString();
		jl::Material& material = MaterialsManager::getInstance().createMaterial(name);

		{
			const std::string shaderPath = value[k_shader].asString();
			jl::Shader* shader = ResourceManager::getInstance().loadShader(shaderPath);
			ASSERT(shader);

			material.setShader(shader);
		}

		restoreMaterialProperties(value[k_properties], material);
	}
}

//-----------------------------------------------------------------------------

void JsonProjectRestorer::restoreMaterialProperties(const Json::Value& _json, jl::Material& _material)
{
	for (const Json::Value& value : _json)
	{
		const std::string name = value[k_name].asString();
		const std::string type = value[k_type].asString();

		const Json::Value& propertyValue = value[k_value];
		switch (utils::fromString<jl::UniformType>(type))
		{
		case jl::UniformType::Int:
			_material.setProperty(name, propertyValue.asInt());
			break;

		case jl::UniformType::Float:
			_material.setProperty(name, propertyValue.asFloat());
			break;

		case jl::UniformType::Vec2:
			_material.setProperty(name, details::jsonToVec2(propertyValue));
			break;

		case jl::UniformType::Vec3:
			_material.setProperty(name, details::jsonToVec3(propertyValue));
			break;

		case jl::UniformType::Vec4:
			_material.setProperty(name, details::jsonToVec4(propertyValue));
			break;

		case jl::UniformType::Texture2D:
			{
				const std::string path = propertyValue.asString();
				if (!path.empty())
				{
					jl::Texture* texture = ResourceManager::getInstance().loadTexture(path);
					ASSERT(texture);
					_material.setProperty(name, texture);
				}
			}
			break;

		case jl::UniformType::CubeTexture:
			{
				const std::string path = propertyValue.asString();
				if (!path.empty())
				{
					jl::CubeTexture* texture = ResourceManager::getInstance().loadCubeTexture(path);
					ASSERT(texture);
					_material.setProperty(name, texture);
				}
			}
			break;

		default:
			ASSERT(0);
		}
	}
}

//-----------------------------------------------------------------------------

void JsonProjectRestorer::restoreScene(const Json::Value& _json)
{
	m_sceneWrapper = std::make_unique<SceneWrapper>();

	for (const Json::Value& object : _json[k_objects])
	{
		restoreObject(object);
	}

	restoreLights(_json[k_lights], m_sceneWrapper->getLightsHolder());
}

//-----------------------------------------------------------------------------

void JsonProjectRestorer::restoreObject(const Json::Value& _json)
{
	std::string objName = _json[k_name].asString();
	ObjectWrapper& wrapper = m_sceneWrapper->createObject(std::move(objName));

	const Json::Value& modelJson = _json[k_model];
	if (!_json.isNull())
	{
		restoreModel(modelJson, wrapper);
	}

	wrapper.setPosition(details::jsonToVec3(_json[k_position]));
	wrapper.setRotation(details::jsonToVec3(_json[k_rotation]));
	wrapper.setSize(details::jsonToVec3(_json[k_size]));
}

//-----------------------------------------------------------------------------

void JsonProjectRestorer::restoreModel(const Json::Value& _json, ObjectWrapper& _objWrapper)
{
	const std::string modelPath = _json[k_path].asString();
	if (modelPath.empty())
	{
		return;
	}

	jl::Model* model = ResourceManager::getInstance().loadModel(modelPath, false /* _loadMaterials */);
	ASSERT(model);
	if (!model)
	{
		return;
	}

	Json::Value::ArrayIndex materialsToRead = 0;

	const Json::Value& meshMaterials = _json[k_meshMaterials];
	if (meshMaterials.isArray())
	{
		materialsToRead = std::min(meshMaterials.size(), static_cast<Json::Value::ArrayIndex>(model->getMeshesCount()));
	}

	for (Json::Value::ArrayIndex i = 0; i < materialsToRead; ++i)
	{
		const std::string materialName = meshMaterials[i].asString();
		if (!materialName.empty())
		{
			jl::Material* material = MaterialsManager::getInstance().findMaterial(materialName);
			ASSERT(material);

			jl::Mesh& mesh = model->getMesh(i);
			mesh.setMaterial(material);
		}
	}

	_objWrapper.setModel(model);
}

//-----------------------------------------------------------------------------

void JsonProjectRestorer::restoreLights(const Json::Value& _json, jl::LightsHolder& _lightsHolder)
{
	for (const Json::Value& light : _json[k_pointLights])
	{
		jl::PointLightData lightData{ details::jsonToVec3(light[k_color]), details::jsonToVec3(light[k_position]) };
		_lightsHolder.addPointLight(lightData);
	}

	for (const Json::Value& light : _json[k_directionalLights])
	{
		jl::DirectionalLightData lightData{ details::jsonToVec3(light[k_color]), details::jsonToVec3(light[k_direction]) };
		_lightsHolder.addDirectionalLight(lightData);
	}

	const Json::Value& ambientlight = _json[k_ambientLight];

	jl::AmbientLightData lightData{ details::jsonToVec3(ambientlight[k_color]), ambientlight[k_weight].asFloat() };
	_lightsHolder.setAmbientLight(lightData);
}

//-----------------------------------------------------------------------------
