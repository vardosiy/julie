#include "save_restore/JsonProjectRestorer.hpp"
#include "save_restore/JsonStrings.hpp"

#include "ObjectWrapper.hpp"

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

std::unique_ptr<jl::Scene> JsonProjectRestorer::extractScene()
{
	return std::move(m_scene);
}

//-----------------------------------------------------------------------------

std::vector<ObjectWrapper> JsonProjectRestorer::extractObjWrappers()
{
	return std::move(m_objWrappers);
}

//-----------------------------------------------------------------------------

void JsonProjectRestorer::restoreMaterials(const Json::Value& _json)
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

void JsonProjectRestorer::restoreMaterialProperties(const Json::Value& _json, jl::Material& _material)
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

void JsonProjectRestorer::restoreScene(const Json::Value& _json)
{
	m_scene = std::make_unique<jl::Scene>();
	m_objWrappers.reserve(_json.size());

	for (const Json::Value& object : _json[k_objects])
	{
		restoreObject(object);
	}

	restoreLights(_json[k_lights], m_scene->getLightsHolder());
}

//-----------------------------------------------------------------------------

void JsonProjectRestorer::restoreObject(const Json::Value& _json)
{
	auto object = std::make_unique<jl::Object>(_json[k_name].asString());

	ObjectWrapper& wrapper = m_objWrappers.emplace_back(*object);
	m_scene->addObject(std::move(object));

	wrapper.setPosition(details::jsonToVec3(_json[k_position]));
	wrapper.setRotation(details::jsonToVec3(_json[k_rotation]));
	wrapper.setScale(details::jsonToVec3(_json[k_scale]));

	{
		const Json::Value& modelJson = _json[k_model];
		if (modelJson.isString() && !modelJson.empty())
		{
			const std::string modelSource = modelJson.asString();
			if (!modelSource.empty())
			{
				jl::Model* model = ResourceManager::getInstance().loadModel(modelJson.asString());
				ASSERT(model);
				if (model)
				{
					wrapper.setModel(*model);
				}
			}
		}
	}
	{
		const Json::Value& materialJson = _json[k_material];
		if (materialJson.isString())
		{
			if (jl::Material* material = MaterialsManager::getInstance().findMaterial(materialJson.asString()))
			{
				wrapper.setMaterial(*material);
			}
		}
	}
}

//-----------------------------------------------------------------------------

void JsonProjectRestorer::restoreLights(const Json::Value& _json, jl::LightsHolder& _lightsHolder)
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
