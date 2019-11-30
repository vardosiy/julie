#pragma once

#include "renderer/scene/lights/AmbientLightData.hpp"
#include "renderer/scene/FogData.hpp"

#include "utils/Singleton.hpp"

#include <json/json.h>
#include <glm/glm.hpp>

#include <string_view>
#include <functional>
#include <memory>

class Camera;
class Light;
class Object;
struct ObjectParameters;

class SceneManager : public utils::Singleton<SceneManager>
{
	friend class utils::Singleton<SceneManager>;

public:
	void init();
	void draw();

	void update(float _deltaTime);

public:
	const Camera & getCamera() const { return *m_camera; }

	const FogData & getFog() const noexcept									{ return m_fogData; }
	const AmbientLightData & getAmbientLightData() const noexcept			{ return m_ambientLightData; }

	const std::vector<glm::vec4> & getDirLightsColors() const noexcept		{ return m_dirLightsColors; }
	const std::vector<glm::vec4> & getPointLightsColors() const noexcept	{ return m_pointLightsColors; }
	const std::vector<glm::vec3> & getLightsDirections() const noexcept		{ return m_lightsDirections; }
	const std::vector<glm::vec3> & getLightsPositions() const noexcept		{ return m_lightsPositions; }

protected:
	SceneManager();
	~SceneManager();

private:
	void loadAmbientLight(const Json::Value & _data);
	void loadCamera(const Json::Value & _data);
	void loadFog(const Json::Value & _data);

	void loadObjects(const Json::Value & _data);
	void loadLights(const Json::Value & _data);

	void prepareLights();
	void updateLightPositions();

	ObjectParameters loadObjectParameters(const Json::Value & _data);

	template<typename T>
	std::vector<T *> loadObjectTextures(
		const std::function<T * (int)>& _textureGetter,
		const Json::Value & _data
	);

private:
	std::unique_ptr<Camera> m_camera;

	FogData m_fogData;
	AmbientLightData m_ambientLightData;

	std::vector<std::unique_ptr<Object>> m_objects;

	std::vector<Light> m_lights;
	std::vector<glm::vec4> m_dirLightsColors;
	std::vector<glm::vec4> m_pointLightsColors;
	std::vector<glm::vec3> m_lightsDirections;
	std::vector<glm::vec3> m_lightsPositions;

	static constexpr std::string_view k_filePath{ "SM.json" };
};
