#include <glad/glad.h>

#include "rendering/shaders/Shader.hpp"
#include "rendering/common/Vertex.hpp"

#include "utils/LogDefs.hpp"
#include "utils/Assert.hpp"

#include <fstream>
#include <sstream>

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

bool checkShaderCompilationSucceded(GLuint _shaderHandle) noexcept
{
	int status;
	glGetShaderiv(_shaderHandle, GL_COMPILE_STATUS, &status);

	if (!status)
	{
		int messageLength;
		glGetShaderiv(_shaderHandle, GL_INFO_LOG_LENGTH, &messageLength);

		if (messageLength > 1)
		{
			char * message = new char[messageLength];

			glGetShaderInfoLog(_shaderHandle, messageLength, nullptr, message);
			LOG_INFO("Shader compile error message: {}", message);

			delete[] message;
		}

		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------

std::string readShaderFile(std::string_view _filePath)
{
	std::string fileContent;

	std::ifstream file(_filePath.data(), std::ios::in);
	if (file.is_open())
	{
		std::stringstream buffer;
		buffer << file.rdbuf();
		fileContent = buffer.str();
	}
	else
	{
		LOG_ERROR("Can't open shader file {}", _filePath);
	}

	return fileContent;
}

//-----------------------------------------------------------------------------

GLuint loadShader(GLenum _type, std::string_view _filePath)
{
	GLuint shader = 0;

	std::string fileContent = readShaderFile(_filePath);
	if (!fileContent.empty())
	{
		shader = glCreateShader(_type);

		const char * c_str = fileContent.c_str();
		glShaderSource(shader, 1, &c_str, nullptr);
		glCompileShader(shader);

		if (!checkShaderCompilationSucceded(shader))
		{
			glDeleteShader(shader);
			shader = 0;
		}
	}

	return shader;
}

//-----------------------------------------------------------------------------

bool checkProgramLinkageSucceded(GLuint _programHandle) noexcept
{
	int status;
	glGetProgramiv(_programHandle, GL_LINK_STATUS, &status);

	if (!status)
	{
		int messageLength;
		glGetProgramiv(_programHandle, GL_INFO_LOG_LENGTH, &messageLength);

		if (messageLength > 1)
		{
			char * message = new char[messageLength];

			glGetProgramInfoLog(_programHandle, messageLength, nullptr, message);
			LOG_INFO("Shading program link error message: {}", message);

			delete[] message;
		}

		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------

GLuint loadProgram(GLuint _vs, GLuint _fs)
{
	GLuint program = glCreateProgram();

	glAttachShader(program, _vs);
	glAttachShader(program, _fs);
	glLinkProgram(program);

	const bool linkedSuccessful = checkProgramLinkageSucceded(program);

	glDetachShader(program, _vs);
	glDetachShader(program, _fs);

	glDeleteShader(_vs);
	glDeleteShader(_fs);

	if (!linkedSuccessful)
	{
		glDeleteProgram(program);
		program = 0;
	}

	return program;
}

//-----------------------------------------------------------------------------

} // namespace details

//-----------------------------------------------------------------------------

std::unique_ptr<Shader> Shader::create(std::string_view _vsPath, std::string_view _fsPath)
{
	std::unique_ptr<Shader> shader;

	if (const GLuint vs = details::loadShader(GL_VERTEX_SHADER, _vsPath))
	{
		if (const GLuint fs = details::loadShader(GL_FRAGMENT_SHADER, _fsPath))
		{
			if (const GLuint program = details::loadProgram(vs, fs))
			{
				shader.reset(new Shader);
				shader->m_program = program;

				shader->bind();
				shader->initAttribs();
				shader->initUniforms();
			}
		}
		else
		{
			glDeleteShader(vs);
		}
	}

	return shader;
}

//-----------------------------------------------------------------------------

Shader::~Shader()
{
	glDeleteProgram(m_program);
}

//-----------------------------------------------------------------------------

Shader::Shader(Shader && _rhs) noexcept
	: m_program(_rhs.m_program)
{
	_rhs.m_program = 0;
}

//-----------------------------------------------------------------------------

Shader & Shader::operator =(Shader && _rhs) noexcept
{
	std::swap(m_program, _rhs.m_program);

	return *this;
}

//-----------------------------------------------------------------------------

void Shader::draw(int _indeciesCount) const
{
	glDrawElements(GL_TRIANGLES, _indeciesCount, GL_UNSIGNED_SHORT, nullptr);
}

//-----------------------------------------------------------------------------

void Shader::bind() const
{
	glUseProgram(m_program);
}

//-----------------------------------------------------------------------------

void Shader::bindAttributes() const
{
	GLfloat * offset = nullptr;
	if (m_attribs.a_posL != -1)
	{
		glEnableVertexAttribArray(m_attribs.a_posL);
		glVertexAttribPointer(m_attribs.a_posL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offset);
	}

	offset += 3;
	if (m_attribs.a_uv != -1)
	{
		glEnableVertexAttribArray(m_attribs.a_uv);
		glVertexAttribPointer(m_attribs.a_uv, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), offset);
	}

	offset += 2;
	if (m_attribs.a_normL != -1)
	{
		glEnableVertexAttribArray(m_attribs.a_normL);
		glVertexAttribPointer(m_attribs.a_normL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offset);
	}

	offset += 3;
	if (m_attribs.a_bitangentL != -1)
	{
		glEnableVertexAttribArray(m_attribs.a_bitangentL);
		glVertexAttribPointer(m_attribs.a_bitangentL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offset);
	}

	offset += 3;
	if (m_attribs.a_tangentL != -1)
	{
		glEnableVertexAttribArray(m_attribs.a_tangentL);
		glVertexAttribPointer(m_attribs.a_tangentL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offset);
	}
}

//-----------------------------------------------------------------------------

const Uniforms & Shader::getUniforms() const noexcept
{
	return m_uniforms;
}

//-----------------------------------------------------------------------------

void Shader::setUniformValue(GLint _location, GLint _val) const
{
	glUniform1i(_location, _val);
}

//-----------------------------------------------------------------------------

void Shader::setUniformValue(GLint _location, GLfloat _val) const
{
	glUniform1f(_location, _val);
}

//-----------------------------------------------------------------------------

void Shader::setUniformValue(GLint _location, const glm::vec2 & _val) const
{
	glUniform2fv(_location, 1, reinterpret_cast<const float *>(&_val));
}

//-----------------------------------------------------------------------------

void Shader::setUniformValue(GLint _location, const glm::vec3 & _val) const
{
	glUniform3fv(_location, 1, reinterpret_cast<const float *>(&_val));
}

//-----------------------------------------------------------------------------

void Shader::setUniformValue(GLint _location, const glm::vec4 & _val) const
{
	glUniform4fv(_location, 1, reinterpret_cast<const float *>(&_val));
}

//-----------------------------------------------------------------------------

void Shader::setUniformValue(GLint _location, const glm::mat4 & _val) const
{
	glUniformMatrix4fv(_location, 1, false, reinterpret_cast<const float *>(&_val));
}

//-----------------------------------------------------------------------------

void Shader::setUniformValue(GLint _location, uint32_t _count, const GLint * _val) const
{
	glUniform1iv(_location, _count, _val);
}

//-----------------------------------------------------------------------------

void Shader::setUniformValue(GLint _location, uint32_t _count, const glm::vec3 * _val) const
{
	glUniform3fv(_location, _count, reinterpret_cast<const float *>(_val));
}

//-----------------------------------------------------------------------------

void Shader::setUniformValue(GLint _location, uint32_t _count, const glm::vec4 * _val) const
{
	glUniform4fv(_location, _count, reinterpret_cast<const float *>(_val));
}

//-----------------------------------------------------------------------------

void Shader::initAttribs()
{
	m_attribs.a_posL		= glGetAttribLocation(m_program, "a_posL");
	m_attribs.a_uv			= glGetAttribLocation(m_program, "a_uv");
	m_attribs.a_normL		= glGetAttribLocation(m_program, "a_normL");
	m_attribs.a_bitangentL	= glGetAttribLocation(m_program, "a_bitangentL");
	m_attribs.a_tangentL	= glGetAttribLocation(m_program, "a_tangentL");
}

//-----------------------------------------------------------------------------

void Shader::initUniforms()
{
	m_uniforms.u_WVP				= glGetUniformLocation(m_program, "u_WVP");

	m_uniforms.u_W					= glGetUniformLocation(m_program, "u_W");
	m_uniforms.u_camPosition		= glGetUniformLocation(m_program, "u_camPosition");

	m_uniforms.u_fogStart			= glGetUniformLocation(m_program, "u_fogStart");
	m_uniforms.u_fogRange			= glGetUniformLocation(m_program, "u_fogRange");
	m_uniforms.u_fogColor			= glGetUniformLocation(m_program, "u_fogColor");

	m_uniforms.u_depthAdjust		= glGetUniformLocation(m_program, "u_depthAdjust");
	m_uniforms.u_tilingFactor		= glGetUniformLocation(m_program, "u_tilingFactor");
	m_uniforms.u_dMax				= glGetUniformLocation(m_program, "u_dMax");
	m_uniforms.u_depthDispl			= glGetUniformLocation(m_program, "u_depthDispl");
	m_uniforms.u_color				= glGetUniformLocation(m_program, "u_color");

	m_uniforms.u_ambientWeight		= glGetUniformLocation(m_program, "u_ambientWeight");
	m_uniforms.u_ambientColor		= glGetUniformLocation(m_program, "u_ambientColor");
	m_uniforms.u_specularPower		= glGetUniformLocation(m_program, "u_specularPower");

	m_uniforms.u_dirLightColor		= glGetUniformLocation(m_program, "u_directionalLightColor");
	m_uniforms.u_pointLightColor	= glGetUniformLocation(m_program, "u_pointLightColor");
	m_uniforms.u_lightDirection		= glGetUniformLocation(m_program, "u_lightDirection");
	m_uniforms.u_lightPosition		= glGetUniformLocation(m_program, "u_lightPosition");

	m_uniforms.u_time				= glGetUniformLocation(m_program, "u_time");

	m_uniforms.u_texture2D			= glGetUniformLocation(m_program, "u_texture2D");
	m_uniforms.u_cubeTexture		= glGetUniformLocation(m_program, "u_cubeTexture");

	m_uniforms.u_step				= glGetUniformLocation(m_program, "u_step");
	m_uniforms.u_limit				= glGetUniformLocation(m_program, "u_limit");

	m_uniforms.u_near				= glGetUniformLocation(m_program, "u_near");
	m_uniforms.u_far				= glGetUniformLocation(m_program, "u_far");
	m_uniforms.u_clarity			= glGetUniformLocation(m_program, "u_clarity");
	m_uniforms.u_fade				= glGetUniformLocation(m_program, "u_fade");
}

//-----------------------------------------------------------------------------
