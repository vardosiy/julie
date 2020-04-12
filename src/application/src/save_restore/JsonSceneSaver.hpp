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

class JsonSceneSaver
{
//-----------------------------------------------------------------------------
public:
	static void save(std::ostream& _stream, const jl::Scene& _scene);

//-----------------------------------------------------------------------------
private:
	static Json::Value saveMaterials();
	static Json::Value saveMaterial(const jl::Material& _material);

	static Json::Value saveScene(const jl::Scene& _scene);
	static Json::Value saveObject(const jl::Object& _object);

	static Json::Value saveLights(const jl::LightsHolder& _lightsHolder);
	static Json::Value savePointLights(const std::vector<glm::vec4>& colors, const std::vector<glm::vec3>& positions);
	static Json::Value saveDirectionalLights(const std::vector<glm::vec4>& colors, const std::vector<glm::vec3>& directions);
};
