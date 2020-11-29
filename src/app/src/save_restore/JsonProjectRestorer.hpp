#pragma once

#include "julie/scene/Scene.hpp"

#include <json/json.h>

#include <istream>
#include <optional>

namespace jl {
class Object;

class Model;
class Material;
class LightsHolder;
}

class JsonProjectRestorer
{
public:
	JsonProjectRestorer(std::istream& _stream);

	std::optional<jl::Scene> extractScene();

private:
	static void restoreMaterials(const Json::Value& _json);
	static void restoreMaterialProperties(const Json::Value& _json, jl::Material& _material);
	static void restoreLights(const Json::Value& _json, jl::LightsHolder& _lightsHolder);

	static jl::Scene			restoreScene(const Json::Value& _json);
	static jl::Scene::ObjectPtr	restoreObject(const Json::Value& _json);
	static jl::Model*			restoreModel(const Json::Value& _json);

private:
	std::optional<jl::Scene> m_scene;
};
