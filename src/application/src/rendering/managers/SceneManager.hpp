#pragma once

#include "rendering/objects/Parameters.hpp"

#include "utils/Singleton.hpp"

#include <json/json.h>
#include <glm/glm.hpp>

#include <string_view>
#include <functional>
#include <memory>

class Fog;
class Object;
class Camera;

class AmbientLight;
class Light;

class SceneManager : public utils::Singleton<SceneManager>
{
	friend class utils::Singleton<SceneManager>;

public:
	void init();
	void draw();

	void update(float _deltaTime);

public:
	Fog & getFog()						{ return *m_fog; }
	Camera & getCamera()				{ return *m_camera; }
	AmbientLight & getAmbientLight()	{ return *m_ambientLight; }

	const std::vector<glm::vec4> & getDirLightsColors()		{ return m_dirLightsColors; }
	const std::vector<glm::vec4> & getPointLightsColors()	{ return m_pointLightsColors; }
	const std::vector<glm::vec3> & getLightsDirections()	{ return m_lightsDirections; }
	const std::vector<glm::vec3> & getLightsPositions()		{ return m_lightsPositions; }

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

	Parameters loadObjectParameters(const Json::Value & _data);

	template<typename T>
	std::vector<T *> loadObjectTextures(
		const std::function<T * (int)>& _textureGetter,
		const Json::Value & _data
	);

private:
	std::unique_ptr<AmbientLight> m_ambientLight;
	std::unique_ptr<Camera> m_camera;
	std::unique_ptr<Fog> m_fog;

	std::vector<std::unique_ptr<Object>> m_objects;

	std::vector<Light> m_lights;
	std::vector<glm::vec4> m_dirLightsColors;
	std::vector<glm::vec4> m_pointLightsColors;
	std::vector<glm::vec3> m_lightsDirections;
	std::vector<glm::vec3> m_lightsPositions;

	static constexpr std::string_view k_filePath{ "SM.json" };
};
