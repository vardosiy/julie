#include "save_restore/JsonSceneRestorer.hpp"
#include "save_restore/JsonStrings.hpp"

#include "managers/ResourceManager.hpp"
#include "managers/MaterialsManager.hpp"

#include "renderer/Material.hpp"
#include "renderer/UniformType.hpp"

#include "renderer/scene/Scene.hpp"
#include "renderer/scene/Object.hpp"
#include "renderer/scene/lights/LightsHolder.hpp"

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

inline glm::vec2 jsonToVec2(const Json::Value& _val) noexcept
{
	return glm::vec2(_val[0].asFloat(), _val[1].asFloat());
}

inline glm::vec3 jsonToVec3(const Json::Value& _val) noexcept
{
	return glm::vec3(_val[0].asFloat(), _val[1].asFloat(), _val[2].asFloat());
}

inline glm::vec4 jsonToVec4(const Json::Value& _val) noexcept
{
	return glm::vec4(_val[0].asFloat(), _val[1].asFloat(), _val[2].asFloat(), _val[3].asFloat());
}

//-----------------------------------------------------------------------------

} // namespace details

//-----------------------------------------------------------------------------

std::unique_ptr<jl::Scene> JsonSceneRestorer::restore(std::istream& _stream)
{
	Json::Value root;
	_stream >> root;

	restoreMaterials(root[k_materials]);
	return restoreScene(root[k_scene]);
}

//-----------------------------------------------------------------------------

void JsonSceneRestorer::restoreMaterials(const Json::Value& _json)
{
	for (const Json::Value& value : _json)
	{
		const std::string& name = value[k_name].asString();
		jl::Material& material = MaterialsManager::getInstance().createMaterial(name);

		{
			const std::string& shaderPath = value[k_shader].asString();
			jl::Shader* shader = ResourceManager::getInstance().loadShader(shaderPath);

			ASSERT(shader);
			if (shader)
			{
				material.setShader(*shader);
			}
		}

		restoreMaterialProperties(value[k_properties], material);
	}
}

//-----------------------------------------------------------------------------

void JsonSceneRestorer::restoreMaterialProperties(const Json::Value& _json, jl::Material& _material)
{
	for (const Json::Value& value : _json)
	{
		const std::string& name = value[k_name].asString();
		const std::string& type = value[k_type].asString();

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
				jl::Texture* texture = ResourceManager::getInstance().loadTexture(propertyValue.asString());
				ASSERT(texture);
				if (texture)
				{
					_material.setProperty(name, *texture);
				}
			}
			break;

		case jl::UniformType::CubeTexture:
			{
				jl::CubeTexture* texture = ResourceManager::getInstance().loadCubeTexture(propertyValue.asString());
				ASSERT(texture);
				if (texture)
				{
					_material.setProperty(name, *texture);
				}
			}
			break;

		default:
			ASSERT(0);
		}
	}
}

//-----------------------------------------------------------------------------

std::unique_ptr<jl::Scene> JsonSceneRestorer::restoreScene(const Json::Value& _json)
{
	auto scene = std::make_unique<jl::Scene>();

	for (const Json::Value& object : _json[k_objects])
	{
		scene->addObject(restoreObject(object));
	}

	restoreLights(_json[k_lights], scene->getLightsHolder());

	return scene;
}

//-----------------------------------------------------------------------------

std::unique_ptr<jl::Object> JsonSceneRestorer::restoreObject(const Json::Value& _json)
{
	auto object = std::make_unique<jl::Object>(_json[k_name].asString());

	object->setPosition(details::jsonToVec3(_json[k_position]));
	object->setRotation(details::jsonToVec3(_json[k_rotation]));
	object->setScale(details::jsonToVec3(_json[k_scale]));

	{
		const Json::Value& modelJson = _json[k_model];
		if (modelJson.isString())
		{
			jl::Model* model = ResourceManager::getInstance().loadModel(modelJson.asString());
			ASSERT(model);
			if (model)
			{
				object->setModel(*model);
			}
		}
	}
	{
		const Json::Value& materialJson = _json[k_material];
		if (materialJson.isString())
		{
			if (jl::Material* material = MaterialsManager::getInstance().getMaterial(materialJson.asString()))
			{
				object->setMaterial(*material);
			}
		}
	}

	return object;
}

//-----------------------------------------------------------------------------

void JsonSceneRestorer::restoreLights(const Json::Value& _json, jl::LightsHolder& _lightsHolder)
{
	for (const Json::Value& light : _json[k_pointLights])
	{
		jl::PointLightData lightData{ details::jsonToVec4(light[k_color]), details::jsonToVec3(light[k_position]) };
		_lightsHolder.addPointLight(lightData);
	}

	for (const Json::Value& light : _json[k_directionalLights])
	{
		jl::DirectionalLightData lightData{ details::jsonToVec4(light[k_color]), details::jsonToVec3(light[k_direction]) };
		_lightsHolder.addDirectionalLight(lightData);
	}

	const Json::Value& ambientlight = _json[k_ambientLight];

	jl::AmbientLightData lightData{ details::jsonToVec4(ambientlight[k_color]), ambientlight[k_weight].asFloat() };
	_lightsHolder.setAmbientLight(lightData);
}

//-----------------------------------------------------------------------------
