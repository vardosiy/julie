//#include "save_restore/JsonSceneSaver.hpp"
//
//#include "renderer/scene/Scene.hpp"
//
//#include "json/json.h"
//
////-----------------------------------------------------------------------------
//
//JsonSceneSaver::JsonSceneSaver(std::ostream& _outputStream)
//	: m_outputStream(_outputStream)
//{
//}
//
////-----------------------------------------------------------------------------
//
//void JsonSceneSaver::save(const jl::Scene& _scene)
//{
//	Json::Value root(Json::objectValue);
//
//	//root["objects"] = saveObjects(_scene);
//
//	if (const jl::FogData* data = _scene.getFogData())
//	{
//		root["fogData"] = saveFogData(*data);
//	}
//	if (const jl::AmbientLightData* data = _scene.getAmbientLightData())
//	{
//		root["ambientLightData"] = saveAmbientLightData(*data);
//	}
//
//	m_outputStream << root;
//}
//
////-----------------------------------------------------------------------------
//
//Json::Value JsonSceneSaver::saveObjects(const jl::Scene& _scene)
//{
//	Json::Value result(Json::arrayValue);
//
//	_scene.forEachObject(
//		[&result](jl::s32 _id, const jl::Object& _object)
//		{
//			Json::Value object(Json::objectValue);
//			object["id"] = _id;
//			object["objectData"] = saveObjectData(_object);
//			result.append(object);
//		}
//	);
//
//	return result;
//}
//
////-----------------------------------------------------------------------------
//
//Json::Value JsonSceneSaver::saveObjectData(const jl::Object& _object)
//{
//	Json::Value result(Json::objectValue);
//
//
//	return result;
//}
//
////-----------------------------------------------------------------------------
//
//Json::Value JsonSceneSaver::saveFogData(const jl::FogData& _fogData)
//{
//
//}
//
////-----------------------------------------------------------------------------
//
//Json::Value JsonSceneSaver::saveAmbientLightData(const jl::AmbientLightData& _fogData)
//{
//
//}
//
////-----------------------------------------------------------------------------
