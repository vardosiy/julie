#pragma once

#include "renderer/scene/FreeflyCamera.hpp"
#include "renderer/Model.hpp"
#include "renderer/Shader.hpp"
#include "renderer/Texture.hpp"
#include "renderer/Material.hpp"

#include <vector>
#include <memory>

class Sandbox
{
public:
	void init();
	void update(float _dt);
	void draw();

	void onWindowResized(jl::u32 _w, jl::u32 _h);

private:
	void initResources();

	std::unique_ptr<jl::FreeflyCamera> m_camera;

	std::vector<std::unique_ptr<jl::Shader>> m_shaders;
	std::vector<std::unique_ptr<jl::Model>> m_models;
	std::vector<std::unique_ptr<jl::Texture>> m_textures;
	std::vector<std::unique_ptr<jl::Material>> m_materials;
};
