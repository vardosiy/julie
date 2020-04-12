#pragma once

#include <json/json.h>

#include <istream>
#include <memory>

namespace jl {
class Scene;
class Object;
class Material;
class LightsHolder;
}

class JsonSceneRestorer
{
public:
	static std::unique_ptr<jl::Scene> restore(std::istream& _stream);

private:
	static void restoreMaterials(const Json::Value& _json);
	static void restoreMaterialProperties(const Json::Value& _json, jl::Material& _material);

	static std::unique_ptr<jl::Scene> restoreScene(const Json::Value& _json);
	static std::unique_ptr<jl::Object> restoreObject(const Json::Value& _json);
	static void restoreLights(const Json::Value& _json, jl::LightsHolder& _lightsHolder);
};
