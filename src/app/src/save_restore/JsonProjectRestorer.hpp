#pragma once

#include <json/json.h>

#include <istream>
#include <memory>

namespace jl {
class Model;
class Material;
class LightsHolder;
}

class SceneWrapper;
class ObjectWrapper;

class JsonProjectRestorer
{
public:
	JsonProjectRestorer(std::istream& _stream);

	std::unique_ptr<SceneWrapper> extractScene();

private:
	static void restoreMaterials(const Json::Value& _json);
	static void restoreMaterialProperties(const Json::Value& _json, jl::Material& _material);

	void restoreScene(const Json::Value& _json);
	void restoreObject(const Json::Value& _json);
	void restoreModel(const Json::Value& _json, ObjectWrapper& _objWrapper);
	static void restoreLights(const Json::Value& _json, jl::LightsHolder& _lightsHolder);

private:
	std::unique_ptr<SceneWrapper> m_sceneWrapper;
};
