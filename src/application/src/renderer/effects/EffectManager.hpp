//#pragma once
//
//#include "Effect.h"
//#include "Fbo.h"
//
//#include "utils/Singleton.hpp"
//
//#include <json/json.h>
//
//#include <string_view>
//#include <vector>
//
//class EffectManager
//{
//public:
//	void init();
//
//	void BindFbo() const;
//	void apply() const;
//
//	void update(float _deltaTime);
//
//private:
//	int loadShaders(const Json::Value & _data);
//
//	void loadFbos(const Json::Value & _data);
//	void loadEffects(const Json::Value & _data);
//
//	Array< Pass > LoadEffectPasses(const Json::Value & _data);
//	Array< float > LoadPassParameters(const Json::Value & _data);
//	Array< TexturePtr > LoadPassTextures(const Json::Value & _data);
//
//private:
//	std::vector<Fbo> m_fbos;
//	std::vector<Effect> m_effects;
//	std::vector<Shader> m_shaders;
//
//	const Effect * m_pCurrentEffect;
//
//	static constexpr std::string_view k_filePath{ "EM.json" };
//};
