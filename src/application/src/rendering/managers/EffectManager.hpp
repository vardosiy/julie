//#pragma once
//
//#include "Aliases.h"
//#include "Array.h"
//#include "Effect.h"
//#include "Fbo.h"
//
//#include <GLES2/gl2.h>
//
//namespace Json
//{
//class Value;
//}
//
//class EffectManager
//{
//public:
//
//	static EffectManager * GetInstance();
//
//	int init();
//
//	void BindFbo() const;
//	void Apply() const;
//
//	void update(float _deltaTime);
//
//protected:
//
//	EffectManager() = default;
//	~EffectManager() = default;
//
//private:
//
//	int LoadShaders(Json::Value & _data);
//
//	void LoadFbos(Json::Value & _data);
//	void LoadEffects(Json::Value & _data);
//
//	Array< Pass > LoadEffectPasses(Json::Value & _data);
//	Array< float > LoadPassParameters(Json::Value & _data);
//	Array< TexturePtr > LoadPassTextures(Json::Value & _data);
//
//private:
//
//	Array< Fbo > m_fbos;
//	Array< Effect > m_effects;
//	Array< Shader > m_shaders;
//
//	const Effect * m_pCurrentEffect;
//
//	const static char * ms_filePath;
//};
