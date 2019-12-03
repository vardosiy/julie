#include "renderer/managers/EffectManager.hpp"
#include "renderer/managers/InputManager.hpp"

#include "renderer/shaders/Shader.hpp"
#include "renderer/gl_primitives/Texture.hpp"

#include "utils/LogDefs.hpp"
#include "utils/Assert.hpp"

#include <glad/glad.h>

#include <fstream>

//-----------------------------------------------------------------------------

namespace {
constexpr char k_numberCharsOffset = 48;
}

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

void EffectManager::init()
{
	std::ifstream file(k_filePath.data(), std::ifstream::in);
	ASSERT(file.is_open(), "File not found {}", k_filePath.data());
	if (!file.is_open())
	{
		return;
	}

	Json::Value doc;
	file >> doc;
	file.close();

	loadShaders(doc["shaders"]);
	loadFbos(doc);
	loadEffects(doc["effects"]);

	Pass::initModel();
	m_pCurrentEffect = nullptr;
}

//-----------------------------------------------------------------------------

void EffectManager::reset()
{
	Pass::destroyModel();
}

//-----------------------------------------------------------------------------

void EffectManager::bindFbo() const
{
	if (m_pCurrentEffect)
	{
		GLint qt_buffer;
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &qt_buffer);
		Fbo::screen.m_id = qt_buffer;

		m_targetingFbos[1]->bind();
	}
}

//-----------------------------------------------------------------------------

void EffectManager::apply() const
{
	if (m_pCurrentEffect)
	{
		m_pCurrentEffect->apply();
	}
}

//-----------------------------------------------------------------------------

void EffectManager::update(float _deltaTime)
{
	InputManager & inputMgr = InputManager::getInstance();

	if (inputMgr.isPressed('C'))
	{
		m_pCurrentEffect = nullptr;
	}
	else
	{
		for (auto & it : m_effects)
		{
			if (inputMgr.isPressed(it.first + k_numberCharsOffset))
			{
				m_pCurrentEffect = &it.second;
				break;
			}
		}
	}
}

//-----------------------------------------------------------------------------

void EffectManager::loadShaders(const Json::Value & _data)
{
	m_shaders.clear();

	const uint32_t shadersCount{ _data.size() };
	for (uint32_t i{ 0 }; i < shadersCount; ++i)
	{
		const Json::Value & current = _data[i];

		const int shaderId{ current["ID"].asInt() };
		const std::string_view vsFile{ current["VS"].asCString() };
		const std::string_view fsFile{ current["FS"].asCString() };

		auto shader = Shader::create(vsFile, fsFile);
		ASSERT(shader, "Can't initialize shader with ID {}", shaderId);
		if (shader)
		{
			m_shaders[shaderId] = std::move(shader);
		}
	}
}

//-----------------------------------------------------------------------------

void EffectManager::loadFbos(const Json::Value & _data)
{
	const uint32_t fboCount{ _data["fbCount"].asUInt() };
	const uint32_t targetingFbosCount{ fboCount + 1 };

	m_fbos.clear();
	m_fbos.reserve(fboCount);

	m_targetingFbos.clear();
	m_targetingFbos.reserve(fboCount);

	m_targetingFbos.push_back(&Fbo::screen);
	for (uint32_t i{ 0 }; i < fboCount; ++i)
	{
		m_fbos.emplace_back(Fbo::create());
		m_targetingFbos.push_back(m_fbos[i].get());
	}
}

//-----------------------------------------------------------------------------

void EffectManager::loadEffects(const Json::Value & _data)
{
	m_effects.clear();

	const uint32_t effectsCount{ _data.size() };
	for (uint32_t i{ 0 }; i < effectsCount; ++i)
	{
		const int effectId{ _data[i]["ID"].asInt() };

		Effect & effect = m_effects[effectId];
		if (!loadEffectPasses(_data[i]["passes"], effect))
		{
			m_effects.erase(effectId);
			LOG_ERROR("Can not initialize effect with id: {}", effectId);
		}
	}
}

//-----------------------------------------------------------------------------

bool EffectManager::loadEffectPasses(const Json::Value & _data, Effect & _effect)
{
	const uint32_t passesCount{ _data.size() };
	for (uint32_t i{ 0 }; i < passesCount; ++i)
	{
		const Json::Value & current = _data[i];
		Pass pass;

		{
			const int targetId{ current["target"].asInt() };
			ASSERT(targetId <= m_targetingFbos.size(), "Can not find FBO with id: {}", targetId);
			if (targetId >= m_targetingFbos.size())
			{
				return false;
			}
			pass.setTarget(*m_targetingFbos[targetId]);
		}

		{
			const int shaderId{ current["shader"].asInt() };
			auto itShader = m_shaders.find(shaderId);

			ASSERT(itShader != m_shaders.end(), "Can not find shader with id: {}", shaderId);
			if (itShader == m_shaders.end())
			{
				return false;
			}
			pass.setShader(*itShader->second);
		}

		pass.setParameters(loadPassParameters(current["parameters"]));
		pass.setTextures(loadPassTextures(current["textures"]));

		_effect.addPass(pass);
	}

	return true;
}

//-----------------------------------------------------------------------------

std::vector<float> EffectManager::loadPassParameters(const Json::Value & _data)
{
	const uint32_t paramsCount{ _data.size() };
	std::vector<float> params(paramsCount);

	for (uint32_t i{ 0 }; i < paramsCount; ++i)
	{
		params[i] = _data[i].asFloat();
	}

	return params;
}

//-----------------------------------------------------------------------------

std::vector<const Texture *> EffectManager::loadPassTextures(const Json::Value & _data)
{
	uint32_t texturesCount{ _data.size() };
	for (uint32_t i{ texturesCount }; i > 0; --i)
	{
		const char * str = _data[i - 1].asCString();
		if (str[0] == '0')
		{
			--texturesCount;
		}
	}

	std::vector<const Texture *> textures(texturesCount);

	for (uint32_t i{ 0 }; i < texturesCount; ++i)
	{
		const char * str = _data[i].asCString();
		const uint32_t fboIndex{ static_cast<uint32_t>(str[0] - k_numberCharsOffset) };

		textures[i] =
			str[1] == 'c' ?
			&m_targetingFbos[fboIndex]->getColorTexture() :
			&m_targetingFbos[fboIndex]->getDepthTexture();
	}

	return textures;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
