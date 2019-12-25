#pragma once

#include "renderer/effects/Effect.hpp"
#include "renderer/gl_primitives/Fbo.hpp"

#include "utils/Singleton.hpp"

#include <json/json.h>

#include <string_view>
#include <vector>
#include <unordered_map>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Shader;

class EffectManager : public utils::Singleton<EffectManager>
{
	friend class utils::Singleton<EffectManager>;

public:
	void init();
	void reset();

	void bindFbo() const;
	void apply() const;

	void update(float _deltaTime);

private:
	void loadShaders(const Json::Value & _data);
	void loadFbos(const Json::Value & _data);
	void loadEffects(const Json::Value & _data);

	bool loadEffectPasses(const Json::Value & _data, Effect & _effect);
	std::vector<float> loadPassParameters(const Json::Value & _data);
	std::vector<const Texture *> loadPassTextures(const Json::Value & _data);

private:
	std::vector<Fbo *> m_targetingFbos;
	std::vector<std::unique_ptr<Fbo>> m_fbos;
	
	std::unordered_map<s32, Effect> m_effects;
	std::unordered_map<s32, std::unique_ptr<Shader>> m_shaders;

	const Effect * m_pCurrentEffect = nullptr;

	static constexpr std::string_view k_filePath = "EM.json";
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
