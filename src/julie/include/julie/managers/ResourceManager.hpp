#pragma once

#include "utils/Singleton.hpp"

#include <unordered_map>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Model;
class Shader;
class Texture;
class CubeTexture;

class ResourceManager : public utils::Singleton<ResourceManager>
{
	friend class utils::Singleton<ResourceManager>;

//-----------------------------------------------------------------------------
public:
	void clear();

	Model*			loadModel(const std::string& _fileName, bool _loadMaterials);
	Shader*			loadShader(const std::string& _fileName);
	Texture*		loadTexture(const std::string& _fileName);
	CubeTexture*	loadCubeTexture(const std::string& _fileName);

	std::string		findSourceFile(const Model& _model) const noexcept;
	std::string		findSourceFile(const Shader& _shader) const noexcept;
	std::string		findSourceFile(const Texture& _texture) const noexcept;
	std::string		findSourceFile(const CubeTexture& _texture) const noexcept;

//-----------------------------------------------------------------------------
private:
	template<typename T>
	using Container = std::unordered_map<std::string, std::unique_ptr<T>>; // source file => resource

	ResourceManager();
	~ResourceManager();

	template<typename T, typename U>
	static T* loadCommon(Container<T>& _container, const std::string& _fileName, U&& _loadFun);

	template<typename T>
	static std::string findSourceFileCommon(const Container<T>& _container, const T& _resource) noexcept;

//-----------------------------------------------------------------------------
	Container<Model> m_models;
	Container<Shader> m_shaders;
	Container<Texture> m_textures;
	Container<CubeTexture> m_cubeTextures;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
