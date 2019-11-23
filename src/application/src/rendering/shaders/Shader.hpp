#pragma once

#include "rendering/common/Attributes.hpp"
#include "rendering/common/Uniforms.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <boost/noncopyable.hpp>

#include <string_view>
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

	const Uniforms & getUniforms() const noexcept;

	void setUniformValue(GLint _location, GLint _val) const;
	void setUniformValue(GLint _location, GLfloat _val) const;
	void setUniformValue(GLint _location, const glm::vec2 & _val) const;
	void setUniformValue(GLint _location, const glm::vec3 & _val) const;
	void setUniformValue(GLint _location, const glm::vec4 & _val) const;
	void setUniformValue(GLint _location, const glm::mat4 & _val) const;

	void setUniformValue(GLint _location, uint32_t _count, const GLint * _val) const;
	void setUniformValue(GLint _location, uint32_t _count, const glm::vec3 * _val) const;
	void setUniformValue(GLint _location, uint32_t _count, const glm::vec4 * _val) const;

private:
	Shader() = default;

	void initAttribs();
	void initUniforms();

private:
	GLuint m_program;

	Attributes m_attribs;
	Uniforms m_uniforms;
};
