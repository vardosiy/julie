#include "save_restore/JsonSceneSaver.hpp"

#include "renderer/scene/Scene.hpp"

#include "json/json.h"

//-----------------------------------------------------------------------------

SceneSaver::SceneSaver(std::ostream& _outputStream)
	: m_outputStream(_outputStream)
{
}

//-----------------------------------------------------------------------------

void SceneSaver::save(const jl::Scene& _scene)
{
	Json::Value root(Json::objectValue);

	Json::Value& objects = root["objects"];
	objects = Json::arrayValue;

	_scene.forEachObject(
		[&objects](jl::s32 _id, const jl::Object& _object)
		{
			Json::Value object(Json::objectValue);
			object["id"] = _id;

			// TODO

			objects.append(object);
		}
	);
}

//-----------------------------------------------------------------------------
