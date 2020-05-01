#include "managers/ResourceManager.hpp"

#include "controllers/AppController.hpp"

#include "managers/factories/ModelsFactory.hpp"
#include "managers/factories/ShadersFactory.hpp"
#include "managers/factories/TexturesFactory.hpp"

#include "renderer/Model.hpp"
#include "renderer/Shader.hpp"
#include "renderer/Texture.hpp"
#include "renderer/CubeTexture.hpp"

//-----------------------------------------------------------------------------

ResourceManager::ResourceManager() = default;
ResourceManager::~ResourceManager() = default;

//-----------------------------------------------------------------------------

void ResourceManager::clear()
{
	m_models.clear();
	m_shaders.clear();
	m_textures.clear();
	m_cubeTextures.clear();
}

//-----------------------------------------------------------------------------

jl::Model* ResourceManager::loadModel(const std::string& _fileName)
{
	return loadCommon(m_models, _fileName, ModelsFactory::loadFromFile);
}

//-----------------------------------------------------------------------------

jl::Shader* ResourceManager::loadShader(const std::string& _fileName)
{
	return loadCommon(m_shaders, _fileName, ShadersFactory::loadFromFile);
}

//-----------------------------------------------------------------------------

jl::Texture* ResourceManager::loadTexture(const std::string& _fileName)
{
	return loadCommon(m_textures, _fileName, TexturesFactory::load2dTextureFromFile);
}

//-----------------------------------------------------------------------------

jl::CubeTexture* ResourceManager::loadCubeTexture(const std::string& _fileName)
{
	return loadCommon(m_cubeTextures, _fileName, TexturesFactory::loadCubeTextureFromFile);
}

//-----------------------------------------------------------------------------

const std::string& ResourceManager::getSourceFile(const jl::Model& _model) const noexcept
{
	return getSourceFileCommon(m_models, _model);
}

//-----------------------------------------------------------------------------

const std::string& ResourceManager::getSourceFile(const jl::Shader& _shader) const noexcept
{
	return getSourceFileCommon(m_shaders, _shader);
}

//-----------------------------------------------------------------------------

const std::string& ResourceManager::getSourceFile(const jl::Texture& _texture) const noexcept
{
	return getSourceFileCommon(m_textures, _texture);
}

//-----------------------------------------------------------------------------

const std::string& ResourceManager::getSourceFile(const jl::CubeTexture& _texture) const noexcept
{
	return getSourceFileCommon(m_cubeTextures, _texture);
}

//-----------------------------------------------------------------------------

template<typename T, typename U>
T* ResourceManager::loadCommon(Container<T>& _container, const std::string& _fileName, U&& _loadFun)
{
	auto it = _container.find(_fileName);
	if (it != _container.end())
	{
		return it->second.get();
	}

	AppController::makeContextCurrent();
	auto [itEmplacedItem, inserted] = _container.emplace(_fileName, _loadFun(_fileName));
	return itEmplacedItem->second.get();
}

//-----------------------------------------------------------------------------

template<typename T>
const std::string& ResourceManager::getSourceFileCommon(const Container<T>& _container, const T& _resource) noexcept
{
	for (const auto& [sourceFile, resource] : _container)
	{
		if (resource.get() == &_resource)
		{
			return sourceFile;
		}
	}
	return "";
}

//-----------------------------------------------------------------------------
