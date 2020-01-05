#pragma once

#include "renderer/Types.hpp"
#include "renderer/ShaderAttributes.hpp"
#include "renderer/ShaderUniforms.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <boost/noncopyable.hpp>

#include <string_view>
#include <vector>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Model;

class Shader : boost::noncopyable
{
public:
	static std::unique_ptr<Shader> create(std::string_view _vsPath, std::string_view _fsPath);

public:
	~Shader();

	void draw(const Model & _model) const;

	void bind() const noexcept;

	const ShaderUniforms & getUniforms() const noexcept;

	void setUniformValue(s32 _location, s32 _val) const;
	void setUniformValue(s32 _location, float _val) const;
	void setUniformValue(s32 _location, const glm::vec2 & _val) const;
	void setUniformValue(s32 _location, const glm::vec3 & _val) const;
	void setUniformValue(s32 _location, const glm::vec4 & _val) const;
	void setUniformValue(s32 _location, const glm::mat4 & _val) const;

	void setUniformValue(s32 _location, const std::vector<s32> & _val) const;
	void setUniformValue(s32 _location, u32 _count, const s32 * _val) const;
	void setUniformValue(s32 _location, u32 _count, const glm::vec3 * _val) const;
	void setUniformValue(s32 _location, u32 _count, const glm::vec4 * _val) const;

private:
	Shader() noexcept = default;

	void initAttribs();
	void initUniforms();

private:
	u32 m_program;

	ShaderAttributes m_attribs;
	ShaderUniforms m_uniforms;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
