#pragma once

#include "utils/Singleton.hpp"

#include <unordered_map>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {
class Model;
class Shader;
class Texture;
}

class ResourceManager : public utils::Singleton<ResourceManager>
{
	friend class utils::Singleton<ResourceManager>;

public:
	void clear();

	std::shared_ptr<jl::Model>		loadModel(const std::string& _fileName);
	std::shared_ptr<jl::Shader>		loadShader(const std::string& _fileName);
	std::shared_ptr<jl::Texture>	loadTexture(const std::string& _fileName);

private:
	template<typename T>
	using Container = std::unordered_map<std::string, std::shared_ptr<T>>; // source file => resource

	ResourceManager();
	~ResourceManager();

	template<typename T, typename U>
	std::shared_ptr<T> loadCommon(Container<T>& _container, const std::string& _fileName, U&& _loadFun);

private:
	Container<jl::Model> m_models;
	Container<jl::Shader> m_shaders;
	Container<jl::Texture> m_textures;
};

//-----------------------------------------------------------------------------
