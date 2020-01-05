#include "managers/ResourceManager.hpp"

#include "renderer/loaders/ModelsFactory.hpp"
#include "renderer/loaders/TexturesFactory.hpp"
#include "renderer/TextureTiling.hpp"

#include "utils/LogDefs.hpp"
#include "utils/Assert.hpp"

#include <json/json.h>
#include <glad/glad.h>

#include <fstream>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

void ResourceManager::init()
{
	std::ifstream file(k_filePath.data(), std::ifstream::in);
	ASSERTM(file.is_open(), "File not found {}", k_filePath.data());
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
	const u32 modelsCount = _data.size();
	for (u32 i = 0; i < modelsCount; ++i)
	{
		const Json::Value & current = _data[i];

		const s32 modelId = current["ID"].asInt();
		const std::string_view fileName = current["file"].asCString();

		auto model = ModelsFactory::loadFromFile(fileName);
		ASSERTM(model, "Can't initialize model with ID {}, file:\n-> {}", modelId, fileName);
		if (model)
		{
			m_models[modelId] = std::move(model);
		}
	}
}

//-----------------------------------------------------------------------------

void ResourceManager::loadShaders(const Json::Value & _data)
{
	const u32 shadersCount = _data.size();
	for (u32 i = 0; i < shadersCount; ++i)
	{
		const Json::Value & current = _data[i];

		const s32 shaderId = current["ID"].asInt();
		const std::string_view vsFile = current["VS"].asCString();
		const std::string_view fsFile = current["FS"].asCString();

		auto shader = Shader::create(vsFile, fsFile);
		ASSERTM(shader, "Can't initialize shader with ID {}, sources:\n-> VS - {}\n-> FS - {}", shaderId, vsFile, fsFile);
		if (shader)
		{
			m_shaders[shaderId] = std::move(shader);
		}
	}
}

//-----------------------------------------------------------------------------

void ResourceManager::loadTextures2D(const Json::Value & _data)
{
	const u32 textures2DCount = _data.size();
	for (u32 i = 0; i < textures2DCount; ++i)
	{
		const Json::Value & current = _data[i];

		const s32 textureId = current["ID"].asInt();
		const std::string_view tiling = current["tiling"].asCString();
		const std::string_view fileName = current["file"].asCString();

		auto texture = TexturesFactory::load2dTextureFromFile(fileName, fromString<TextureTiling>(tiling));
		ASSERTM(texture, "Can't load 2D texture with ID {}, file:\n-> {}", textureId, fileName);
		if (texture)
		{
			m_textures2D[textureId] = std::move(texture);
		}
	}
}

//-----------------------------------------------------------------------------

void ResourceManager::loadCubeTextures(const Json::Value & _data)
{
	const u32 cubeTexturesCount = _data.size();
	for (u32 i = 0; i < cubeTexturesCount; ++i)
	{
		const Json::Value & current = _data[i];

		const s32 textureId = current["ID"].asInt();
		const std::string_view tiling = current["tiling"].asCString();
		const std::string_view fileName = current["file"].asCString();

		auto texture = TexturesFactory::loadCubeTextureFromFile(fileName, fromString<TextureTiling>(tiling));
		ASSERTM(texture, "Can't load cube texture with ID {}, file:\n-> {}", textureId, fileName);
		if (texture)
		{
			m_cubeTextures[textureId] = std::move(texture);
		}
	}
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
