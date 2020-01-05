#pragma once

#include "renderer/scene/Camera.hpp"
#include "renderer/Model.hpp"
#include "renderer/Shader.hpp"
#include "renderer/Texture.hpp"

#include <vector>
#include <memory>

class Sandbox
{
public:
	void init();
	void update(float _dt);
	void draw();

private:
	std::unique_ptr<jl::Camera> m_camera;

	std::vector<std::unique_ptr<jl::Shader>> m_shaders;
	std::vector<std::unique_ptr<jl::Model>> m_models;
	std::vector<std::unique_ptr<jl::Texture>> m_textures;
};
