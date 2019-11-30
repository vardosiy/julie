#include "renderer/scene/ResourceManager.hpp"
#include "renderer/scene/objects/Object.hpp"

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
	ASSERT(file.is_open(), "File not found {}", k_filePath.data());
	if (!file.is_open())
	{
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
		const int modelId{ current["ID"].asInt() };
		const std::string_view fileName{ current["file"].asCString() };

		auto model = Model::create(fileName);
		ASSERT(model, "Can't initialize model with ID {}", modelId);
		if (model)
		{
			m_models[modelId] = std::move(model);
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

		const int shaderId{ current["ID"].asInt() };
		const std::string_view vs{ current["VS"].asCString() };
		const std::string_view fs{ current["FS"].asCString() };

		auto shader = Shader::create(vs, fs);
		ASSERT(shader, "Can't initialize shader with ID {}", shaderId);
		if (shader)
		{
			m_shaders[shaderId] = std::move(shader);
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

		const int textureId{ current["ID"].asInt() };
		const GLenum tiling{ details::getTilingFromStr(current["tiling"].asString()) };
		const std::string_view fileName{ current["file"].asCString() };

		auto texture = Texture::create(fileName, tiling);
		ASSERT(texture, "Can't load 2D texture with ID {}", textureId);
		if (texture)
		{
			m_textures2D[textureId] = std::move(texture);
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

		const int textureId{ current["ID"].asInt() };
		const GLenum tiling{ details::getTilingFromStr(current["tiling"].asString()) };
		const std::string_view fileName{ current["file"].asCString() };

		auto texture = CubeTexture::create(fileName, tiling);
		ASSERT(texture, "Can't load 2D texture with ID {}", textureId);
		if (texture)
		{
			m_cubeTextures[textureId] = std::move(texture);
		}
	}
}

//-----------------------------------------------------------------------------
