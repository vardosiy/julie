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

class ObjectWrapper;

class JsonProjectRestorer
{
public:
	JsonProjectRestorer(std::istream& _stream);

	std::unique_ptr<jl::Scene> extractScene();
	std::vector<ObjectWrapper> extractObjWrappers();

private:
	static void restoreMaterials(const Json::Value& _json);
	static void restoreMaterialProperties(const Json::Value& _json, jl::Material& _material);

	void restoreScene(const Json::Value& _json);
	void restoreObject(const Json::Value& _json);
	static void restoreLights(const Json::Value& _json, jl::LightsHolder& _lightsHolder);

private:
	std::unique_ptr<jl::Scene> m_scene;
	std::vector<ObjectWrapper> m_objWrappers;
};
