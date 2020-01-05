#pragma once

#include "renderer/Types.hpp"

#include <glm/vec2.hpp>

#include <vector>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Fbo;
class Shader;
class Texture;
class Model;

class Pass
{
public:
	Pass() noexcept = default;

	void setTarget(const Fbo & _target) noexcept;
	void setShader(const Shader & _shader) noexcept;
	void setParameters(const std::vector<float> & _parameters) noexcept;
	void setTextures(const std::vector<const Texture *> & _textures) noexcept;

	void run() const;

	static void initModel();
	static void destroyModel();

private:
	void initBlurOffsets();

private:
	const Fbo * m_target;
	const Shader * m_shader;

	std::vector<float> m_parameters;
	std::vector<s32> m_texureUniformValue;
	std::vector<const Texture *> m_textures;

	glm::vec2 m_blurOffsets;

	bool m_bIsDof;
	bool m_bIsBlur;

	static std::unique_ptr<Model> ms_model;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
