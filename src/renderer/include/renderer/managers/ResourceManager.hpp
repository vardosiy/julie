#pragma once

#include "renderer/common/Types.hpp"
#include "renderer/shaders/Shader.hpp"
#include "renderer/scene/Model.hpp"
#include "renderer/gl_primitives/Texture.hpp"
#include "renderer/gl_primitives/CubeTexture.hpp"

#include "utils/Singleton.hpp"

#include <json/json.h>

#include <string_view>
#include <map>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class ResourceManager : public utils::Singleton<ResourceManager>
{
	friend class utils::Singleton<ResourceManager>;

public:
	void init();
	void clear();

	Model * getModel(s32 _id) const noexcept				{ return findById<Model>(_id, m_models); }
	Shader * getShader(s32 _id) const noexcept				{ return findById<Shader>(_id, m_shaders); }
	Texture * get2dTexture(s32 _id) const noexcept			{ return findById<Texture>(_id, m_textures2D); }
	CubeTexture * getCubeTexture(s32 _id) const noexcept	{ return findById<CubeTexture>(_id, m_cubeTextures); }

private:
	void loadModels(const Json::Value & _data);
	void loadShaders(const Json::Value & _data);
	void loadTextures2D(const Json::Value & _data);
	void loadCubeTextures(const Json::Value & _data);

	template<typename T>
	static T * findById(s32 _id, const std::map<s32, std::unique_ptr<T>> & _container);

private:
	std::map<s32, std::unique_ptr<Model>> m_models;
	std::map<s32, std::unique_ptr<Shader>> m_shaders;
	std::map<s32, std::unique_ptr<Texture>> m_textures2D;
	std::map<s32, std::unique_ptr<CubeTexture>> m_cubeTextures;

	std::unique_ptr<Model> m_generatedTerrainModel;

	static constexpr std::string_view k_filePath = "RM.json";
};

//-----------------------------------------------------------------------------

template<typename T>
T * ResourceManager::findById(s32 _id, const std::map<s32, std::unique_ptr<T>> & _container)
{
	auto it = _container.find(_id);
	return it != _container.end() ? it->second.get() : nullptr;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
