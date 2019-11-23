//#include "stdafx.h"
//
//#include "EffectManager.h"
//#include "inputManager.h"
//
//#include "Shader.h"
//#include "Texture.h"
//
//#include <json/json.h>
//
//#include <fstream>
//
////-----------------------------------------------------------------------------
//
//const char * EffectManager::ms_filePath = "EM.json";
//
////-----------------------------------------------------------------------------
//
//EffectManager * EffectManager::GetInstance()
//{
//	static EffectManager s_instane;
//	return &s_instane;
//}
//
////-----------------------------------------------------------------------------
//
//int EffectManager::init()
//{
//	std::ifstream file(ms_filePath, std::ifstream::in);
//	if (!file.is_open())
//	{
//		printf("Error: File not found %s\n", ms_filePath);
//		return -1;
//	}
//
//	Json::Value doc;
//	file >> doc;
//
//	file.close();
//
//	if (LoadShaders(doc["shaders"]) != 0)
//		return -2;
//
//	LoadFbos(doc);
//	LoadEffects(doc["effects"]);
//
//	Pass::InitModel();
//	m_pCurrentEffect = nullptr;
//
//	return 0;
//}
//
////-----------------------------------------------------------------------------
//
//void EffectManager::BindFbo() const
//{
//	int fboIndex = m_pCurrentEffect ? 1 : 0;
//
//	m_fbos[fboIndex].bind();
//}
//
////-----------------------------------------------------------------------------
//
//void EffectManager::Apply() const
//{
//	if (!m_pCurrentEffect)
//		return;
//
//	m_pCurrentEffect->Apply();
//}
//
////-----------------------------------------------------------------------------
//
//void EffectManager::update(float _deltaTime)
//{
//	InputManager * inputMngr = InputManager::GetInstance();
//	const int effectsCount = m_effects.GetSize();
//
//	if (inputMngr->IsPressed('0'))
//		m_pCurrentEffect = nullptr;
//
//	else if (inputMngr->IsPressed('1') && effectsCount >= 1)
//		m_pCurrentEffect = &m_effects[0];
//
//	else if (inputMngr->IsPressed('2') && effectsCount >= 2)
//		m_pCurrentEffect = &m_effects[1];
//
//	else if (inputMngr->IsPressed('3') && effectsCount >= 3)
//		m_pCurrentEffect = &m_effects[2];
//
//	else if (inputMngr->IsPressed('4') && effectsCount >= 4)
//		m_pCurrentEffect = &m_effects[3];
//}
//
////-----------------------------------------------------------------------------
//
//int EffectManager::LoadShaders(Json::Value & _data)
//{
//	const int shadersCount = _data.size();
//	m_shaders = Array< Shader >(shadersCount);
//
//	for (int i = 0; i < shadersCount; ++i)
//	{
//		Json::Value & current = _data[i];
//
//		const int shaderID = current["ID"].asInt();
//		const char * VS = current["VS"].asCString();
//		const char * FS = current["FS"].asCString();
//
//		if (m_shaders[shaderID].init(VS, FS) != 0)
//		{
//			printf("Error: can't initialize shader with ID %d\n", shaderID);
//			return -1;
//		}
//	}
//
//	return 0;
//}
//
////-----------------------------------------------------------------------------
//
//void EffectManager::LoadFbos(Json::Value & _data)
//{
//	// just a trick here, fbo on idx 0 will not initialized,
//	// so it's ID == 0 and when we will bind it,
//	// it will actually unbind any framebuffers,
//	// thats why we allocating one extra Fbo
//
//	const int requestedFboCount = _data["fbCount"].asInt();
//	const int actualFboCout = requestedFboCount + 1;
//
//	m_fbos = Array< Fbo >(actualFboCout);
//
//	for (int i = 1; i < actualFboCout; ++i)
//		m_fbos[i].init();
//}
//
////-----------------------------------------------------------------------------
//
//void EffectManager::LoadEffects(Json::Value & _data)
//{
//	const int effectsCount = _data.size();
//	m_effects = Array< Effect >(effectsCount);
//
//	for (int i = 0; i < effectsCount; ++i)
//	{
//		m_effects[i].init(
//			LoadEffectPasses(_data[i]["passes"])
//		);
//	}
//}
//
////-----------------------------------------------------------------------------
//
//Array< Pass > EffectManager::LoadEffectPasses(Json::Value & _data)
//{
//	const int passesCount = _data.size();
//	Array< Pass > passes(passesCount);
//
//	for (int i = 0; i < passesCount; ++i)
//	{
//		Json::Value & current = _data[i];
//
//		const int passID = current["ID"].asInt();
//
//		const int target = current["target"].asInt();
//		passes[passID].SetTarget(&m_fbos[target]);
//
//		const int shaderID = current["shader"].asInt();
//		passes[passID].SetShader(&m_shaders[shaderID]);
//
//		Array< float > passParameters = LoadPassParameters(current["parameters"]);
//		passes[passID].SetParameters(std::move(passParameters));
//
//		Array< TexturePtr > textures = LoadPassTextures(current["textures"]);
//		passes[passID].SetTextures(std::move(textures));
//	}
//
//	return passes;
//}
//
////-----------------------------------------------------------------------------
//
//Array< float > EffectManager::LoadPassParameters(Json::Value & _data)
//{
//	const int paramsCount = _data.size();
//	Array< float > params(paramsCount);
//
//	for (int i = 0; i < paramsCount; ++i)
//		params[i] = _data[i].asFloat();
//
//	return params;
//}
//
////-----------------------------------------------------------------------------
//
//Array< TexturePtr > EffectManager::LoadPassTextures(Json::Value & _data)
//{
//	int texturesCount = _data.size();
//	for (int i = texturesCount - 1; i >= 0; --i)
//	{
//		const char * str = _data[i].asCString();
//		if (str[0] == '0')
//			--texturesCount;
//	}
//
//	Array< TexturePtr > textures(texturesCount);
//
//	for (int i = 0; i < texturesCount; ++i)
//	{
//		constexpr int k_esNumberCharsOffset = 48;
//
//		const char * str = _data[i].asCString();
//		const int fboIndex = str[0] - k_esNumberCharsOffset;
//
//		str[1] == 'c' ?
//			textures[i] = m_fbos[fboIndex].getColorTexture() :
//			textures[i] = m_fbos[fboIndex].getDepthTexture();
//	}
//
//	return textures;
//}
//
////-----------------------------------------------------------------------------
