#include "renderer/managers/SceneManager.hpp"
#include "renderer/managers/ResourceManager.hpp"

#include "renderer/scene/Camera.hpp"
#include "renderer/scene/Model.hpp"
#include "renderer/scene/Object.hpp"
#include "renderer/scene/AmbientLightData.hpp"
#include "renderer/scene/Light.hpp"

#include "renderer/common/Axis.hpp"

#include "utils/LogDefs.hpp"
#include "utils/Assert.hpp"

#include <fstream>

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

static glm::vec3 jsonArrayToVec3(const Json::Value & _array)
{
	return glm::vec3{ _array[0].asFloat(), _array[1].asFloat(), _array[2].asFloat() };
}

//-----------------------------------------------------------------------------

static jl::Light::Type lightTypeFromString(std::string_view _str)
{
	if (_str == "directional")
	{
		return jl::Light::Type::Directional;
	}
	else if (_str == "point")
	{
		return jl::Light::Type::Point;
	}

	ASSERT(false, "Unknown light type");
	return jl::Light::Type::Directional;
}

//-----------------------------------------------------------------------------

} // namespace details

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

SceneManager::SceneManager() = default;

//-----------------------------------------------------------------------------

SceneManager::~SceneManager() = default;

//-----------------------------------------------------------------------------

void SceneManager::init()
{
	std::ifstream file(k_filePath.data(), std::ifstream::in);
	if (!file.is_open())
	{
		LOG_ERROR("File not found {}", k_filePath.data());
		return;
	}

	Json::Value doc;
	file >> doc;
	file.close();

	loadObjects(doc["objects"]);
	loadAmbientLight(doc["ambient_light"]);
	loadLights(doc["lights"]);
	loadFog(doc["fog"]);
	loadCamera(doc["camera"]);

	prepareLights();
}

//-----------------------------------------------------------------------------

void SceneManager::draw()
{
	for (auto & object : m_objects)
	{
		object->draw();
	}
}

//-----------------------------------------------------------------------------

void SceneManager::update(float _deltaTime)
{
	m_camera->update(_deltaTime);

	for (auto & object : m_objects)
	{
		object->update(_deltaTime);
	}
	for (auto & light : m_lights)
	{
		light.update(_deltaTime);
	}

	updateLightPositions();
}

//-----------------------------------------------------------------------------

void SceneManager::loadAmbientLight(const Json::Value & _data)
{
	if (_data.empty())
	{
		LOG_WARNING("Ambient light is not described in SM.json, setting default values");
	}

	m_ambientLightData.color = glm::vec4(details::jsonArrayToVec3(_data["color"]), 1.0f);
	m_ambientLightData.weight = _data["weight"].asFloat();
}

//-----------------------------------------------------------------------------

void SceneManager::loadFog(const Json::Value & _data)
{
	if (_data.empty())
	{
		LOG_WARNING("Fog is not described in SM.json, setting default values");
	}

	m_fogData.color = glm::vec4(details::jsonArrayToVec3(_data["color"]), 0.0f);
	m_fogData.start = _data["start"].asFloat();
	m_fogData.range = _data["range"].asFloat();
}

//-----------------------------------------------------------------------------

void SceneManager::loadCamera(const Json::Value & _data)
{
	if (_data.empty())
	{
		LOG_WARNING("Camera is not described in SM.json, setting default values");
	}

	const float camNear{ _data["near"].asFloat() };
	const float camFar{ _data["far"].asFloat() };
	const float camFov{ _data["fov"].asFloat() };

	m_camera = std::make_unique<Camera>(camNear, camFar, camFov);

	m_camera->setMoveSpeed(_data["speed"].asFloat());
	m_camera->setRotationSpeed(_data["rot_speed"].asFloat());

	m_camera->setPosition(details::jsonArrayToVec3(_data["position"]));
	m_camera->setRotation(details::jsonArrayToVec3(_data["rotation"]));
	m_camera->setUpVector(constants::axis::y);
}

//-----------------------------------------------------------------------------

void SceneManager::loadObjects(const Json::Value & _data)
{
	ResourceManager & resManager = ResourceManager::getInstance();

	auto tex2dGetter = [&resManager](int _id) { return resManager.get2dTexture(_id); };
	auto cubeTexGetter = [&resManager](int _id) { return resManager.getCubeTexture(_id); };

	const uint32_t objectsCount{ _data.size() };
	m_objects.reserve(objectsCount);

	for (uint32_t i{ 0 }; i < objectsCount; ++i)
	{
		const Json::Value & current = _data[i];

		const int modelId{ current["model"].asInt() };
		Model * model = resManager.getModel(modelId);
		if (!model)
		{
			continue;
		}

		std::unique_ptr<Object> & object = m_objects.emplace_back(Object::create(*model));

		const int shaderId{ current["shader"].asInt() };
		Shader * shader = resManager.getShader(shaderId);
		if (shader)
		{
			object->setShader(*shader);
		}

		auto textures2D = loadObjectTextures<Texture>(tex2dGetter, current["2Dtex"]);
		object->setTextures2D(std::move(textures2D));

		auto cubeTextures = loadObjectTextures<CubeTexture>(cubeTexGetter, current["cubeTex"]);
		object->setCubeTextures(std::move(cubeTextures));

		object->setPosition(details::jsonArrayToVec3(current["position"]));
		object->setRotation(details::jsonArrayToVec3(current["rotation"]));
		object->setScale(details::jsonArrayToVec3(current["scale"]));

		object->setParameters(loadObjectParameters(current["parameters"]));
	}
}

//-----------------------------------------------------------------------------

void SceneManager::loadLights(const Json::Value & _data)
{
	const uint32_t lightsCount{ _data.size() };
	m_lights.reserve(lightsCount);

	for (uint32_t i{ 0 }; i < lightsCount; ++i)
	{
		const Json::Value & current = _data[i];

		Light::Type lightType = details::lightTypeFromString(current["type"].asString());
		if (lightType != Light::Type::Directional && lightType != Light::Type::Point)
		{
			LOG_WARNING("Unknown light type on light {}, setting default value", i);
		}

		const glm::vec3 posDir{ details::jsonArrayToVec3(current["pos_dir"]) };
		const glm::vec4 color{ details::jsonArrayToVec3(current["color"]), 1.0f };
		const float moveSpeed{ current["speed"].asFloat() };
		const float radius{ current["radius"].asFloat() };

		Light & light = m_lights.emplace_back(lightType, posDir);
		light.setColor(color);
		light.setMoveSpeed(moveSpeed);
		light.setRadius(radius);
	}
}

//-----------------------------------------------------------------------------

void SceneManager::prepareLights()
{
	for (auto & light : m_lights)
	{
		switch (light.getType())
		{
			case Light::Type::Directional:
				m_lightsDirections.emplace_back(light.getPosDir());
				m_dirLightsColors.emplace_back(light.getColor());
				break;

			case Light::Type::Point:
				m_lightsPositions.emplace_back(light.getPosDir());
				m_pointLightsColors.emplace_back(light.getColor());
				break;

			default:
				assert(0);
		}
	}
}

//-----------------------------------------------------------------------------

void SceneManager::updateLightPositions()
{
	std::size_t counter{ 0 };
	for (auto & light : m_lights)
	{
		if (light.getType() == Light::Type::Point)
		{
			m_lightsPositions[counter++] = light.getPosDir();
		}
	}
}

//-----------------------------------------------------------------------------

ObjectParameters SceneManager::loadObjectParameters(const Json::Value & _data)
{
	ObjectParameters params;

	params.depthDispl		= _data["depth_displ"].asFloat();
	params.depthAdjust		= _data["depth_adjust"].asFloat();
	params.dMax				= _data["dMax"].asFloat();
	params.specularPower	= _data["specular_power"].asFloat();
	params.tilingFactor		= _data["tiling_factor"].asFloat();
	params.color			= glm::vec4{ details::jsonArrayToVec3(_data["color"]), 1.0f };

	return params;
}

//-----------------------------------------------------------------------------

template<typename T>
std::vector<T *> SceneManager::loadObjectTextures(
	const std::function<T * (int)> & _textureGetter,
	const Json::Value & _data
)
{
	const uint32_t texturesCount{ _data.size() };

	std::vector<T *> textures;
	textures.reserve(texturesCount);
	for (uint32_t i{ 0 }; i < texturesCount; ++i)
	{
		T * texture = _textureGetter(_data[i].asInt());
		if (texture)
		{
			textures.emplace_back(texture);
		}
		else
		{
			LOG_ERROR("Not fount texture with id {}", _data[i].asInt());
		}
	}

	return textures;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
