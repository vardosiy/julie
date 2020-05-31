#pragma once

#include <json/json.h>
#include <glm/glm.hpp>

#include <ostream>

namespace jl {
class Scene;
class Object;
class Material;
class LightsHolder;
}

class ObjectWrapper;

class JsonProjectSaver
{
public:
	static void save(std::ostream& _stream, const jl::Scene& _scene, const std::vector<ObjectWrapper>& _objWrappers);

private:
	static Json::Value saveMaterials();
	static Json::Value saveMaterial(const jl::Material& _material);

	static Json::Value saveScene(const jl::Scene& _scene, const std::vector<ObjectWrapper>& _objWrappers);
	static Json::Value saveObject(const ObjectWrapper& _objWrapper);

	static Json::Value saveLights(const jl::LightsHolder& _lightsHolder);
	static Json::Value savePointLights(const std::vector<glm::vec4>& colors, const std::vector<glm::vec3>& positions);
	static Json::Value saveDirectionalLights(const std::vector<glm::vec4>& colors, const std::vector<glm::vec3>& directions);
};
