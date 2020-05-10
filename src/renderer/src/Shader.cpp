#include "renderer/Shader.hpp"
#include "renderer/Vertex.hpp"
#include "renderer/Model.hpp"

#include "creation_helper/ShaderCrationHelper.hpp"

#include "utils/Utils.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

std::unique_ptr<Shader> Shader::loadFromFile(std::string_view _filePath)
{
	return ShaderCrationHelper::loadFromFile(_filePath);
}

//-----------------------------------------------------------------------------

std::unique_ptr<Shader> Shader::loadFromFiles(std::string_view _vsPath, std::string_view _fsPath)
{
	return ShaderCrationHelper::loadFromFiles(_vsPath, _fsPath);
}

//-----------------------------------------------------------------------------

std::unique_ptr<Shader> Shader::create(std::string_view _vsSource, std::string_view _fsSource)
{
	std::unique_ptr<Shader> shader;

	if (const u32 vs = loadShader(GL_VERTEX_SHADER, _vsSource))
	{
		if (const u32 fs = loadShader(GL_FRAGMENT_SHADER, _fsSource))
		{
			if (const u32 program = loadProgram(vs, fs))
			{
				shader.reset(new Shader(program));
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

Shader::Shader(u32 _programId)
	: m_programId(_programId)
{
}

//-----------------------------------------------------------------------------

Shader::~Shader()
{
	glDeleteProgram(m_programId);
}

//-----------------------------------------------------------------------------

void Shader::bind() const noexcept
{
	glUseProgram(m_programId);
}

//-----------------------------------------------------------------------------

bool Shader::hasUniform(const std::string& _name) const noexcept
{
	return getUniformLocation(_name) != -1;
}

//-----------------------------------------------------------------------------

void Shader::setUniform(const std::string& _name, s32 _val) const
{
	glUniform1i(getUniformLocation(_name), _val);
}

//-----------------------------------------------------------------------------

void Shader::setUniform(const std::string& _name, float _val) const
{
	glUniform1f(getUniformLocation(_name), _val);
}

//-----------------------------------------------------------------------------

void Shader::setUniform(const std::string& _name, const glm::vec2& _val) const
{
	glUniform2f(getUniformLocation(_name), _val.x, _val.y);
}

//-----------------------------------------------------------------------------

void Shader::setUniform(const std::string& _name, const glm::vec3& _val) const
{
	glUniform3f(getUniformLocation(_name), _val.x, _val.y, _val.z);
}

//-----------------------------------------------------------------------------

void Shader::setUniform(const std::string& _name, const glm::vec4& _val) const
{
	glUniform4f(getUniformLocation(_name), _val.x, _val.y, _val.z, _val.w);
}

//-----------------------------------------------------------------------------

void Shader::setUniform(const std::string& _name, const glm::mat4& _val) const
{
	glUniformMatrix4fv(getUniformLocation(_name), 1, false, glm::value_ptr(_val));
}

//-----------------------------------------------------------------------------

void Shader::setUniform(const std::string& _name, u32 _count, const s32* _val) const
{
	glUniform1iv(getUniformLocation(_name), _count, _val);
}

//-----------------------------------------------------------------------------

void Shader::setUniform(const std::string& _name, u32 _count, const glm::vec3* _val) const
{
	glUniform3fv(getUniformLocation(_name), _count, reinterpret_cast<const float*>(_val));
}

//-----------------------------------------------------------------------------

void Shader::setUniform(const std::string& _name, u32 _count, const glm::vec4* _val) const
{
	glUniform4fv(getUniformLocation(_name), _count, reinterpret_cast<const float*>(_val));
}

//-----------------------------------------------------------------------------

s32 Shader::getUniformLocation(const std::string& _name) const
{
	s32 location = -1;

	auto it = m_uniformLocationsCache.find(_name);
	if (it != m_uniformLocationsCache.end())
	{
		location = it->second;
	}
	else
	{
		location = glGetUniformLocation(m_programId, _name.c_str());
		m_uniformLocationsCache[_name] = location;
	}

	return location;
}

//-----------------------------------------------------------------------------

u32 Shader::loadShader(u32 _type, std::string_view _source) noexcept
{
	ASSERT(!_source.empty());
	if (_source.empty())
	{
		return 0;
	}

	s32 shader = glCreateShader(_type);

	const char* c_str = _source.data();
	glShaderSource(shader, 1, &c_str, nullptr);
	glCompileShader(shader);

	if (!checkShaderCompilationSucceded(shader))
	{
		glDeleteShader(shader);
		shader = 0;
	}

	return shader;
}

//-----------------------------------------------------------------------------

u32 Shader::loadProgram(u32 _vsId, u32 _fsId) noexcept
{
	u32 program = glCreateProgram();

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

bool Shader::checkShaderCompilationSucceded(u32 _shaderId) noexcept
{
	s32 status;
	glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &status);

	if (!status)
	{
		s32 messageLength;
		glGetShaderiv(_shaderId, GL_INFO_LOG_LENGTH, &messageLength);

		if (messageLength > 1)
		{
			char* message = new char[messageLength];

			glGetShaderInfoLog(_shaderId, messageLength, nullptr, message);
			LOG_INFO("Shader compile error message: {}", message);

			delete[] message;
		}

		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------

bool Shader::checkProgramLinkageSucceded(u32 _programId) noexcept
{
	s32 status;
	glGetProgramiv(_programId, GL_LINK_STATUS, &status);

	if (!status)
	{
		s32 messageLength;
		glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &messageLength);

		if (messageLength > 1)
		{
			char* message = new char[messageLength];

			glGetProgramInfoLog(_programId, messageLength, nullptr, message);
			LOG_INFO("Shading program link error message: {}", message);

			delete[] message;
		}

		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
