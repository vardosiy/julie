#pragma once

#include <json/json.h>
#include <glm/glm.hpp>

#include <ostream>

namespace jl {
class Model;
class Material;
class LightsHolder;
}

class SceneWrapper;
class ObjectWrapper;

class JsonProjectSaver
{
public:
	static void save(std::ostream& _stream, const SceneWrapper& _sceneWrapper);

private:
	static Json::Value saveMaterials();
	static Json::Value saveMaterial(const jl::Material& _material);

	static Json::Value saveScene(const SceneWrapper& _sceneWrapper);
	static Json::Value saveObject(const ObjectWrapper& _objWrapper);
	static Json::Value saveModel(const jl::Model& _model);

	static Json::Value saveLights(const jl::LightsHolder& _lightsHolder);
	static Json::Value savePointLights(const std::vector<glm::vec3>& colors, const std::vector<glm::vec3>& positions);
	static Json::Value saveDirectionalLights(const std::vector<glm::vec3>& colors, const std::vector<glm::vec3>& directions);
};
