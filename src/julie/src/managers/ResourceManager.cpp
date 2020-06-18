#include "julie/managers/ResourceManager.hpp"
#include "julie/managers/AppController.hpp"

#include "julie/Model.hpp"
#include "julie/Shader.hpp"
#include "julie/Texture.hpp"
#include "julie/CubeTexture.hpp"

#include "utils/Utils.hpp"

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

jl::Model* ResourceManager::loadModel(const std::string& _fileName, bool _loadMaterials)
{
	return loadCommon(m_models, _fileName, [_loadMaterials](const std::string& _fileName)
	{
		return jl::Model::loadFromFile(_fileName, _loadMaterials);
	});
}

//-----------------------------------------------------------------------------

jl::Shader* ResourceManager::loadShader(const std::string& _fileName)
{
	return loadCommon(m_shaders, _fileName, jl::Shader::loadFromFile);
}

//-----------------------------------------------------------------------------

jl::Texture* ResourceManager::loadTexture(const std::string& _fileName)
{
	return loadCommon(m_textures, _fileName, jl::Texture::loadFromFile);
}

//-----------------------------------------------------------------------------

jl::CubeTexture* ResourceManager::loadCubeTexture(const std::string& _fileName)
{
	return loadCommon(m_cubeTextures, _fileName, jl::CubeTexture::loadFromFile);
}

//-----------------------------------------------------------------------------

const std::string& ResourceManager::findSourceFile(const jl::Model& _model) const noexcept
{
	return findSourceFileCommon(m_models, _model);
}

//-----------------------------------------------------------------------------

const std::string& ResourceManager::findSourceFile(const jl::Shader& _shader) const noexcept
{
	return findSourceFileCommon(m_shaders, _shader);
}

//-----------------------------------------------------------------------------

const std::string& ResourceManager::findSourceFile(const jl::Texture& _texture) const noexcept
{
	return findSourceFileCommon(m_textures, _texture);
}

//-----------------------------------------------------------------------------

const std::string& ResourceManager::findSourceFile(const jl::CubeTexture& _texture) const noexcept
{
	return findSourceFileCommon(m_cubeTextures, _texture);
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

	LOG_INFO("[ResourceManager] Loading resource from: {}", _fileName.c_str());

	AppController::makeContextCurrent();
	if (std::unique_ptr<T> resource = _loadFun(_fileName))
	{
		auto [itEmplacedItem, inserted] = _container.emplace(_fileName, std::move(resource));
		return itEmplacedItem->second.get();
	}

	return nullptr;
}

//-----------------------------------------------------------------------------

template<typename T>
const std::string& ResourceManager::findSourceFileCommon(const Container<T>& _container, const T& _resource) noexcept
{
	for (const auto& [sourceFile, resource] : _container)
	{
		if (resource.get() == &_resource)
		{
			return sourceFile;
		}
	}

	static const std::string k_runtimeModelSource = "";
	return k_runtimeModelSource;
}

//-----------------------------------------------------------------------------
