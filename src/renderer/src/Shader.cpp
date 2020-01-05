#include "renderer/Shader.hpp"

#include "renderer/Vertex.hpp"
#include "renderer/Model.hpp"

#include "utils/LogDefs.hpp"
#include "utils/Assert.hpp"

#include <glad/glad.h>

#include <fstream>
#include <sstream>

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

bool checkShaderCompilationSucceded(jl::u32 _shaderId) noexcept
{
	jl::s32 status;
	glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &status);

	if (!status)
	{
		jl::s32 messageLength;
		glGetShaderiv(_shaderId, GL_INFO_LOG_LENGTH, &messageLength);

		if (messageLength > 1)
		{
			char * message = new char[messageLength];

			glGetShaderInfoLog(_shaderId, messageLength, nullptr, message);
			LOG_INFO("Shader compile error message: {}", message);

			delete[] message;
		}

		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------

std::string readShaderFile(std::string_view _filePath)
{
	std::string fileContent;

	std::ifstream file(_filePath.data(), std::ios::in);
	ASSERTM(file.is_open(), "Can't open shader file {}", _filePath.data());
	if (file.is_open())
	{
		std::stringstream buffer;
		buffer << file.rdbuf();
		fileContent = buffer.str();
	}

	return fileContent;
}

//-----------------------------------------------------------------------------

int loadShader(jl::u32 _type, std::string_view _filePath)
{
	jl::s32 shader = 0;

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

bool checkProgramLinkageSucceded(jl::u32 _programId) noexcept
{
	jl::s32 status;
	glGetProgramiv(_programId, GL_LINK_STATUS, &status);

	if (!status)
	{
		jl::s32 messageLength;
		glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &messageLength);

		if (messageLength > 1)
		{
			char * message = new char[messageLength];

			glGetProgramInfoLog(_programId, messageLength, nullptr, message);
			LOG_INFO("Shading program link error message: {}", message);

			delete[] message;
		}

		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------

jl::u32 loadProgram(jl::u32 _vsId, jl::u32 _fsId)
{
	jl::u32 program = glCreateProgram();

	glAttachShader(program, _vsId);
	glAttachShader(program, _fsId);
	glLinkProgram(program);

	const bool linkedSuccessful = checkProgramLinkageSucceded(program);

	glDetachShader(program, _vsId);
	glDetachShader(program, _fsId);

	glDeleteShader(_vsId);
	glDeleteShader(_fsId);

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

namespace jl {

//-----------------------------------------------------------------------------

std::unique_ptr<Shader> Shader::create(std::string_view _vsPath, std::string_view _fsPath)
{
	std::unique_ptr<Shader> shader;

	if (const u32 vs = details::loadShader(GL_VERTEX_SHADER, _vsPath))
	{
		if (const u32 fs = details::loadShader(GL_FRAGMENT_SHADER, _fsPath))
		{
			if (const u32 program = details::loadProgram(vs, fs))
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

void Shader::draw(const Model& _model) const
{
	_model.bind();
	glDrawElements(GL_TRIANGLES, _model.getIndeciesCount(), GL_UNSIGNED_SHORT, nullptr);
}

//-----------------------------------------------------------------------------

void Shader::bind() const noexcept
{
	glUseProgram(m_program);
}

//-----------------------------------------------------------------------------

const ShaderUniforms & Shader::getUniforms() const noexcept
{
	return m_uniforms;
}

//-----------------------------------------------------------------------------

void Shader::setUniformValue(s32 _location, s32 _val) const
{
	glUniform1i(_location, _val);
}

//-----------------------------------------------------------------------------

void Shader::setUniformValue(s32 _location, float _val) const
{
	glUniform1f(_location, _val);
}

//-----------------------------------------------------------------------------

void Shader::setUniformValue(s32 _location, const glm::vec2 & _val) const
{
	glUniform2fv(_location, 1, reinterpret_cast<const float *>(&_val));
}

//-----------------------------------------------------------------------------

void Shader::setUniformValue(s32 _location, const glm::vec3 & _val) const
{
	glUniform3fv(_location, 1, reinterpret_cast<const float *>(&_val));
}

//-----------------------------------------------------------------------------

void Shader::setUniformValue(s32 _location, const glm::vec4 & _val) const
{
	glUniform4fv(_location, 1, reinterpret_cast<const float *>(&_val));
}

//-----------------------------------------------------------------------------

void Shader::setUniformValue(s32 _location, const glm::mat4 & _val) const
{
	glUniformMatrix4fv(_location, 1, false, reinterpret_cast<const float *>(&_val));
}

//-----------------------------------------------------------------------------

void Shader::setUniformValue(s32 _location, const std::vector<s32> & _val) const
{
	glUniform1iv(_location, static_cast<s32>(_val.size()), _val.data());
}

//-----------------------------------------------------------------------------

void Shader::setUniformValue(s32 _location, u32 _count, const s32 * _val) const
{
	glUniform1iv(_location, _count, _val);
}

//-----------------------------------------------------------------------------

void Shader::setUniformValue(s32 _location, u32 _count, const glm::vec3 * _val) const
{
	glUniform3fv(_location, _count, reinterpret_cast<const float *>(_val));
}

//-----------------------------------------------------------------------------

void Shader::setUniformValue(s32 _location, u32 _count, const glm::vec4 * _val) const
{
	glUniform4fv(_location, _count, reinterpret_cast<const float *>(_val));
}

//-----------------------------------------------------------------------------

void Shader::initAttribs()
{
	memset(&m_attribs, -1, sizeof(m_attribs));

	m_attribs.a_posL		= glGetAttribLocation(m_program, "a_posL");
	m_attribs.a_uv			= glGetAttribLocation(m_program, "a_uv");
	m_attribs.a_normL		= glGetAttribLocation(m_program, "a_normL");
	m_attribs.a_bitangentL	= glGetAttribLocation(m_program, "a_bitangentL");
	m_attribs.a_tangentL	= glGetAttribLocation(m_program, "a_tangentL");
}

//-----------------------------------------------------------------------------

void Shader::initUniforms()
{
	memset(&m_uniforms, -1, sizeof(m_uniforms));

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

} // namespace jl

//-----------------------------------------------------------------------------
