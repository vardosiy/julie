#pragma once

#include "renderer/shaders/ShaderAttributes.hpp"
#include "renderer/shaders/ShaderUniforms.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <boost/noncopyable.hpp>

#include <string_view>
#include <cstdint>
#include <memory>

class Shader : boost::noncopyable
{
public:
	static std::unique_ptr<Shader> create(std::string_view _vsPath, std::string_view _fsPath);

public:
	~Shader();

	Shader(Shader && _rhs) noexcept;
	Shader & operator =(Shader && _rhs) noexcept;

	void draw(int _indeciesCount) const;

	void bind() const;
	void bindAttributes() const;

	const ShaderUniforms & getUniforms() const noexcept;

	void setUniformValue(int _location, int _val) const;
	void setUniformValue(int _location, float _val) const;
	void setUniformValue(int _location, const glm::vec2 & _val) const;
	void setUniformValue(int _location, const glm::vec3 & _val) const;
	void setUniformValue(int _location, const glm::vec4 & _val) const;
	void setUniformValue(int _location, const glm::mat4 & _val) const;

	void setUniformValue(int _location, uint32_t _count, const int * _val) const;
	void setUniformValue(int _location, uint32_t _count, const glm::vec3 * _val) const;
	void setUniformValue(int _location, uint32_t _count, const glm::vec4 * _val) const;

private:
	Shader() noexcept = default;

	void initAttribs();
	void initUniforms();

private:
	uint32_t m_program;

	ShaderAttributes m_attribs;
	ShaderUniforms m_uniforms;
};
