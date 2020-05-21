#pragma once

#include "utils/Singleton.hpp"

#include <unordered_map>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {
class Model;
class Shader;
class Texture;
class CubeTexture;
}

class ResourceManager : public utils::Singleton<ResourceManager>
{
	friend class utils::Singleton<ResourceManager>;

//-----------------------------------------------------------------------------
public:
	void clear();

	jl::Model*			loadModel(const std::string& _fileName);
	jl::Shader*			loadShader(const std::string& _fileName);
	jl::Texture*		loadTexture(const std::string& _fileName);
	jl::CubeTexture*	loadCubeTexture(const std::string& _fileName);

	const std::string&	findSourceFile(const jl::Model& _model) const noexcept;
	const std::string&	findSourceFile(const jl::Shader& _shader) const noexcept;
	const std::string&	findSourceFile(const jl::Texture& _texture) const noexcept;
	const std::string&	findSourceFile(const jl::CubeTexture& _texture) const noexcept;

//-----------------------------------------------------------------------------
private:
	template<typename T>
	using Container = std::unordered_map<std::string, std::unique_ptr<T>>; // source file => resource

	ResourceManager();
	~ResourceManager();

	template<typename T, typename U>
	static T* loadCommon(Container<T>& _container, const std::string& _fileName, U&& _loadFun);

	template<typename T>
	static const std::string& findSourceFileCommon(const Container<T>& _container, const T& _resource) noexcept;

//-----------------------------------------------------------------------------
	Container<jl::Model> m_models;
	Container<jl::Shader> m_shaders;
	Container<jl::Texture> m_textures;
	Container<jl::CubeTexture> m_cubeTextures;
};

//-----------------------------------------------------------------------------
