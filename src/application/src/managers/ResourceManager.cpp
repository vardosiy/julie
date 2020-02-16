//#include "managers/ResourceManager.hpp"
//
//#include "utils/LogDefs.hpp"
//#include "utils/Assert.hpp"
//
//#include <fstream>
//
////-----------------------------------------------------------------------------
//
////void ResourceManager::init()
////{
////	std::ifstream file(k_filePath.data(), std::ifstream::in);
////	ASSERTM(file.is_open(), "File not found {}", k_filePath.data());
////	if (!file.is_open())
////	{
////		return;
////	}
////
////	Json::Value doc;
////	file >> doc;
////	file.close();
////
////	loadModels(doc["models"]);
////	loadShaders(doc["shaders"]);
////	loadTextures2D(doc["2DTextures"]);
////	loadCubeTextures(doc["cubeTextures"]);
////}
//
////-----------------------------------------------------------------------------
//
//void ResourceManager::clear()
//{
//	m_models.clear();
//	m_shaders.clear();
//	m_textures.clear();
//}
//
////-----------------------------------------------------------------------------
//
//void ResourceManager::add(int _id, std::unique_ptr<jl::Model>&& _model) noexcept
//{
//	ASSERTM(m_models.find(_id) == m_models.end(), "Model with ID: {} already exists, it will be overriden");
//	m_models.emplace(_id, std::move(_model));
//}
//
////-----------------------------------------------------------------------------
//
//void ResourceManager::add(int _id, std::unique_ptr<jl::Shader>&& _shader) noexcept
//{
//	ASSERTM(m_shaders.find(_id) == m_shaders.end(), "Shader with ID: {} already exists, it will be overriden");
//	m_shaders.emplace(_id, std::move(_shader));
//}
//
////-----------------------------------------------------------------------------
//
//void ResourceManager::add(int _id, std::unique_ptr<jl::Texture>&& _texture) noexcept
//{
//	ASSERTM(m_textures.find(_id) == m_textures.end(), "Texture with ID: {} already exists, it will be overriden");
//	m_textures.emplace(_id, std::move(_texture));
//}
//
////-----------------------------------------------------------------------------
//
//jl::Model* ResourceManager::findModel(int _id) const noexcept
//{
//	return findById<jl::Model>(_id, m_models);
//}
//
////-----------------------------------------------------------------------------
//
//jl::Shader* ResourceManager::findShader(int _id) const noexcept
//{
//	return findById<jl::Shader>(_id, m_shaders);
//}
//
////-----------------------------------------------------------------------------
//
//jl::Texture* ResourceManager::find2dTexture(int _id) const noexcept
//{
//	return findById<jl::Texture>(_id, m_textures);
//}
//
////-----------------------------------------------------------------------------
//
//boost::optional<int> ResourceManager::findId(const jl::Model& _model) const noexcept
//{
//	return findResourceId(m_models, _model);
//}
//
////-----------------------------------------------------------------------------
//
//boost::optional<int> ResourceManager::findId(const jl::Shader& _shader) const noexcept
//{
//	return findResourceId(m_shaders, _shader);
//}
//
////-----------------------------------------------------------------------------
//
//boost::optional<int> ResourceManager::findId(const jl::Texture& _texture) const noexcept
//{
//	return findResourceId(m_textures, _texture);
//}
//
////-----------------------------------------------------------------------------
//
//template<typename T>
//T* ResourceManager::findById(int _id, const Container<T>& _container)
//{
//	auto it = _container.find(_id);
//	return it != _container.end() ? it->second.get() : nullptr;
//}
//
////-----------------------------------------------------------------------------
//
//template<typename T>
//boost::optional<int> ResourceManager::findResourceId(const Container<T>& _container, const T& _resource)
//{
//	for (const auto& kv : _container)
//	{
//		if (kv.second.get() == &_resource)
//		{
//			return kv.first;
//		}
//	}
//	return boost::none;
//}
//
////-----------------------------------------------------------------------------
//
////void ResourceManager::loadModels(const Json::Value & _data)
////{
////	const u32 modelsCount = _data.size();
////	for (u32 i = 0; i < modelsCount; ++i)
////	{
////		const Json::Value & current = _data[i];
////
////		const s32 modelId = current["ID"].asInt();
////		const std::string_view fileName = current["file"].asCString();
////
////		auto model = ModelsFactory::loadFromFile(fileName);
////		ASSERTM(model, "Can't initialize model with ID {}, file:\n-> {}", modelId, fileName);
////		if (model)
////		{
////			m_models[modelId] = std::move(model);
////		}
////	}
////}
////
//////-----------------------------------------------------------------------------
////
////void ResourceManager::loadShaders(const Json::Value & _data)
////{
////	const u32 shadersCount = _data.size();
////	for (u32 i = 0; i < shadersCount; ++i)
////	{
////		const Json::Value & current = _data[i];
////
////		const s32 shaderId = current["ID"].asInt();
////		const std::string_view vsFile = current["VS"].asCString();
////		const std::string_view fsFile = current["FS"].asCString();
////
////		auto shader = Shader::create(vsFile, fsFile);
////		ASSERTM(shader, "Can't initialize shader with ID {}, sources:\n-> VS - {}\n-> FS - {}", shaderId, vsFile, fsFile);
////		if (shader)
////		{
////			m_shaders[shaderId] = std::move(shader);
////		}
////	}
////}
////
//////-----------------------------------------------------------------------------
////
////void ResourceManager::loadTextures2D(const Json::Value & _data)
////{
////	const u32 textures2DCount = _data.size();
////	for (u32 i = 0; i < textures2DCount; ++i)
////	{
////		const Json::Value & current = _data[i];
////
////		const s32 textureId = current["ID"].asInt();
////		const std::string_view tiling = current["tiling"].asCString();
////		const std::string_view fileName = current["file"].asCString();
////
////		auto texture = TexturesFactory::load2dTextureFromFile(fileName, fromString<TextureTiling>(tiling));
////		ASSERTM(texture, "Can't load 2D texture with ID {}, file:\n-> {}", textureId, fileName);
////		if (texture)
////		{
////			m_textures2D[textureId] = std::move(texture);
////		}
////	}
////}
////
//////-----------------------------------------------------------------------------
////
////void ResourceManager::loadCubeTextures(const Json::Value & _data)
////{
////	const u32 cubeTexturesCount = _data.size();
////	for (u32 i = 0; i < cubeTexturesCount; ++i)
////	{
////		const Json::Value & current = _data[i];
////
////		const s32 textureId = current["ID"].asInt();
////		const std::string_view tiling = current["tiling"].asCString();
////		const std::string_view fileName = current["file"].asCString();
////
////		auto texture = TexturesFactory::loadCubeTextureFromFile(fileName, fromString<TextureTiling>(tiling));
////		ASSERTM(texture, "Can't load cube texture with ID {}, file:\n-> {}", textureId, fileName);
////		if (texture)
////		{
////			m_cubeTextures[textureId] = std::move(texture);
////		}
////	}
////}
//
////-----------------------------------------------------------------------------
