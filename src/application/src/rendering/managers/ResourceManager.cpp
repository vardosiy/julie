#include "rendering/managers/ResourceManager.hpp"

#include "rendering/objects/Object.hpp"

#include "utils/LogDefs.hpp"
#include "utils/Assert.hpp"

#include <json/json.h>

#include <fstream>

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

static GLenum getTilingFromStr(std::string_view _str)
{
	if (_str == "CLAMP_TO_EDGE")
	{
		return GL_CLAMP_TO_EDGE;
	}
	else if (_str == "REPEAT")
	{
		return GL_REPEAT;
	}

	return 0;
}

//-----------------------------------------------------------------------------

} // namespace details

//-----------------------------------------------------------------------------

void ResourceManager::init()
{
	std::ifstream file(k_filePath.data(), std::ifstream::in);
	if (!file.is_open())
	{
		LOG_ERROR("File not found {}", k_filePath);
		return;
	}

	Json::Value doc;
	file >> doc;
	file.close();

	loadModels(doc["models"]);
	loadShaders(doc["shaders"]);
	loadTextures2D(doc["2DTextures"]);
	loadCubeTextures(doc["cubeTextures"]);
}

//-----------------------------------------------------------------------------

void ResourceManager::clear()
{
	m_models.clear();
	m_shaders.clear();
	m_textures2D.clear();
	m_cubeTextures.clear();
}

//-----------------------------------------------------------------------------

void ResourceManager::loadModels(const Json::Value & _data)
{
	const uint32_t modelsCount{ _data.size() };
	for (uint32_t i{ 0 }; i < modelsCount; ++i)
	{
		const Json::Value & current = _data[i];
		const int modelID{ current["ID"].asInt() };
		const std::string_view fileName{ current["file"].asCString() };

		if (auto model = Model::create(fileName))
		{
			m_models[modelID] = std::move(model);
		}
		else
		{
			LOG_ERROR("Can't initialize model with ID {}", modelID);
		}
	}
}

//-----------------------------------------------------------------------------

void ResourceManager::loadShaders(const Json::Value & _data)
{
	const uint32_t shadersCount{ _data.size() };
	for (uint32_t i{ 0 }; i < shadersCount; ++i)
	{
		const Json::Value & current = _data[i];

		const int shaderID{ current["ID"].asInt() };
		const std::string_view VS{ current["VS"].asCString() };
		const std::string_view FS{ current["FS"].asCString() };

		if (auto shader = Shader::create(VS, FS))
		{
			m_shaders[shaderID] = std::move(shader);
		}
		else
		{
			LOG_ERROR("Can't initialize shader with ID {}", shaderID);
		}
	}
}

//-----------------------------------------------------------------------------

void ResourceManager::loadTextures2D(const Json::Value & _data)
{
	const uint32_t textures2DCount{ _data.size() };
	for (uint32_t i{ 0 }; i < textures2DCount; ++i)
	{
		const Json::Value & current = _data[i];

		const int textureID{ current["ID"].asInt() };
		const GLenum tiling{ details::getTilingFromStr(current["tiling"].asString()) };
		const std::string_view fileName{ current["file"].asCString() };

		if (auto texture = Texture::create(fileName, tiling))
		{
			m_textures2D[textureID] = std::move(texture);
		}
		else
		{
			LOG_ERROR("Can't load 2D texture with ID {}", textureID);
		}
	}
}

//-----------------------------------------------------------------------------

void ResourceManager::loadCubeTextures(const Json::Value & _data)
{
	const uint32_t cubeTexturesCount{ _data.size() };
	for (uint32_t i{ 0 }; i < cubeTexturesCount; ++i)
	{
		const Json::Value & current = _data[i];

		const int textureID{ current["ID"].asInt() };
		const GLenum tiling{ details::getTilingFromStr(current["tiling"].asString()) };
		const std::string_view fileName{ current["file"].asCString() };

		if (auto texture = CubeTexture::create(fileName, tiling))
		{
			m_cubeTextures[textureID] = std::move(texture);
		}
		else
		{
			LOG_ERROR("Can't load cube texture with ID {}", textureID);
		}
	}
}

//-----------------------------------------------------------------------------
