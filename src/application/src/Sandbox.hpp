#pragma once

#include "renderer/shaders/Shader.hpp"
#include "renderer/scene/Model.hpp"
#include "renderer/gl_primitives/Texture.hpp"

#include <vector>
#include <memory>

class Sandbox
{
public:
	void init();
	void update(float _dt);
	void draw();

private:
	std::vector<std::unique_ptr<jl::Shader>> m_shaders;
	std::vector<std::unique_ptr<jl::Model>> m_models;
	std::vector<std::unique_ptr<jl::Texture>> m_textures;
};
