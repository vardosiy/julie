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

//-----------------------------------------------------------------------------
public:
	void clear();

	jl::Model*		loadModel(const std::string& _fileName);
	jl::Shader*		loadShader(const std::string& _fileName);
	jl::Texture*	loadTexture(const std::string& _fileName);

//-----------------------------------------------------------------------------
private:
	template<typename T>
	using Container = std::unordered_map<std::string, std::unique_ptr<T>>; // source file => resource

	ResourceManager();
	~ResourceManager();

	template<typename T, typename U>
	T* loadCommon(Container<T>& _container, const std::string& _fileName, U&& _loadFun);

//-----------------------------------------------------------------------------
	Container<jl::Model> m_models;
	Container<jl::Shader> m_shaders;
	Container<jl::Texture> m_textures;
};

//-----------------------------------------------------------------------------
