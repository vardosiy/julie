#pragma once

#include "renderer/Shader.hpp"
#include "renderer/Model.hpp"
#include "renderer/Texture.hpp"

#include <boost/optional.hpp>
#include <unordered_map>

class ResourceManager
{
public:
	void clear();

	void add(int _id, std::unique_ptr<jl::Model>&& _model) noexcept;
	void add(int _id, std::unique_ptr<jl::Shader>&& _shader) noexcept;
	void add(int _id, std::unique_ptr<jl::Texture>&& _texture) noexcept;

	jl::Model* findModel(int _id) const noexcept;
	jl::Shader* findShader(int _id) const noexcept;
	jl::Texture* find2dTexture(int _id) const noexcept;

private:
	template<typename T>
	using Container = std::unordered_map<int, std::unique_ptr<T>>;

	template<typename T>
	static T* findById(int _id, const Container<T>& _container);

	template<typename T>
	static boost::optional<int> findResourceId(const Container<T>& _container, const T& _resource);

private:
	Container<jl::Model> m_models;
	Container<jl::Shader> m_shaders;
	Container<jl::Texture> m_textures;
};
