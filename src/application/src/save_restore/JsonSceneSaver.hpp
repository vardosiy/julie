//#pragma once
//
//#include "save_restore/ISceneSaver.hpp"
//
//#include "json/json.h"
//
//#include <string_view>
//#include <ostream>
//
//namespace jl {
//class Object;
//class FogData;
//class AmbientLightData;
//}
//
//class JsonSceneSaver : public ISceneSaver
//{
//public:
//	JsonSceneSaver(std::ostream& _outputStream);
//
//	void save(const jl::Scene& _scene) override;
//
//private:
//	static Json::Value saveObjects(const jl::Scene& _scene);
//	static Json::Value saveObjectData(const jl::Object& _object);
//	static Json::Value saveFogData(const jl::FogData& _fogData);
//	static Json::Value saveAmbientLightData(const jl::AmbientLightData& _fogData);
//
//private:
//	std::ostream& m_outputStream;
//};
