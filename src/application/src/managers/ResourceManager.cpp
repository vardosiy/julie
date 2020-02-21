#include "managers/ResourceManager.hpp"

#include "renderer/Model.hpp"
#include "renderer/Shader.hpp"
#include "renderer/Texture.hpp"

#include "renderer/loaders/ModelsFactory.hpp"
#include "renderer/loaders/ShadersFactory.hpp"
#include "renderer/loaders/TexturesFactory.hpp"

#include "utils/Utils.hpp"

//-----------------------------------------------------------------------------

void ResourceManager::clear()
{
	m_models.clear();
	m_shaders.clear();
	m_textures.clear();
}

//-----------------------------------------------------------------------------

std::shared_ptr<jl::Model> ResourceManager::loadModel(const std::string& _fileName)
{
	return loadCommon(m_models, _fileName, jl::ModelsFactory::loadFromFile);
}

//-----------------------------------------------------------------------------

std::shared_ptr<jl::Shader> ResourceManager::loadShader(const std::string& _fileName)
{
	//return loadCommon(m_shaders, _fileName, jl::ShadersFactory::load);

	return nullptr;
	//auto it = _container.find(_fileName);
	//if (it != _container.end())
	//{
	//	return it->second;
	//}
	//
	//std::shared_ptr<T>& resourcePtr = _container[_fileName];
	//resourcePtr = _loadFun(_fileName);
	//
	//return resourcePtr;
}

//-----------------------------------------------------------------------------

std::shared_ptr<jl::Texture> ResourceManager::loadTexture(const std::string& _fileName)
{
	return loadCommon(m_textures, _fileName, jl::TexturesFactory::load2dTextureFromFile);
}

//-----------------------------------------------------------------------------

template<typename T, typename U>
std::shared_ptr<T> ResourceManager::loadCommon(Container<T>& _container, const std::string& _fileName, U&& _loadFun)
{
	auto it = _container.find(_fileName);
	if (it != _container.end())
	{
		return it->second;
	}

	std::shared_ptr<T>& resourcePtr = _container[_fileName];
	resourcePtr = _loadFun(_fileName);

	return resourcePtr;
}

//-----------------------------------------------------------------------------
