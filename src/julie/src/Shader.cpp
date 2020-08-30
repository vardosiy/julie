#include "julie/Shader.hpp"
#include "julie/Vertex.hpp"
#include "julie/Model.hpp"

#include "creation_helpers/ShaderCreationHelper.hpp"

#include "utils/Utils.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

std::unique_ptr<Shader> Shader::loadFromFile(std::string_view _filePath)
{
	return ShaderCreationHelper::loadFromFile(_filePath);
}

//-----------------------------------------------------------------------------

std::unique_ptr<Shader> Shader::loadFromFiles(std::string_view _vsPath, std::string_view _fsPath)
{
	return ShaderCreationHelper::loadFromFiles(_vsPath, _fsPath);
}

//-----------------------------------------------------------------------------

std::unique_ptr<Shader> Shader::create(std::string_view _vsSource, std::string_view _fsSource)
{
	if (_vsSource.empty() || _fsSource.empty())
	{
		return nullptr;
	}

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
	return findUniformLocation(_name) != k_locationUndefined;
}

//-----------------------------------------------------------------------------

void Shader::setUniform(const std::string& _name, s32 _val) const noexcept
{
	const s32 uniformLocation = findUniformLocation(_name);
	if (uniformLocation != k_locationUndefined)
	{
		glUniform1i(uniformLocation, _val);
	}
}

//-----------------------------------------------------------------------------

void Shader::setUniform(const std::string& _name, float _val) const noexcept
{
	const s32 uniformLocation = findUniformLocation(_name);
	if (uniformLocation != k_locationUndefined)
	{
		glUniform1f(uniformLocation, _val);
	}
}

//-----------------------------------------------------------------------------

void Shader::setUniform(const std::string& _name, const glm::vec2& _val) const noexcept
{
	const s32 uniformLocation = findUniformLocation(_name);
	if (uniformLocation != k_locationUndefined)
	{
		glUniform2f(uniformLocation, _val.x, _val.y);
	}
}

//-----------------------------------------------------------------------------

void Shader::setUniform(const std::string& _name, const glm::vec3& _val) const noexcept
{
	const s32 uniformLocation = findUniformLocation(_name);
	if (uniformLocation != k_locationUndefined)
	{
		glUniform3f(uniformLocation, _val.x, _val.y, _val.z);
	}
}

//-----------------------------------------------------------------------------

void Shader::setUniform(const std::string& _name, const glm::vec4& _val) const noexcept
{
	const s32 uniformLocation = findUniformLocation(_name);
	if (uniformLocation != k_locationUndefined)
	{
		glUniform4f(uniformLocation, _val.x, _val.y, _val.z, _val.w);
	}
}

//-----------------------------------------------------------------------------

void Shader::setUniform(const std::string& _name, const glm::mat4& _val) const noexcept
{
	const s32 uniformLocation = findUniformLocation(_name);
	if (uniformLocation != k_locationUndefined)
	{
		glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(_val));
	}
}

//-----------------------------------------------------------------------------

void Shader::setUniform(const std::string& _name, u32 _count, const s32* _val) const noexcept
{
	const s32 uniformLocation = findUniformLocation(_name);
	if (uniformLocation != k_locationUndefined)
	{
		glUniform1iv(uniformLocation, _count, _val);
	}
}

//-----------------------------------------------------------------------------

void Shader::setUniform(const std::string& _name, u32 _count, const glm::vec3* _val) const noexcept
{
	const s32 uniformLocation = findUniformLocation(_name);
	if (uniformLocation != k_locationUndefined)
	{
		glUniform3fv(uniformLocation, _count, reinterpret_cast<const float*>(_val));
	}
}

//-----------------------------------------------------------------------------

void Shader::setUniform(const std::string& _name, u32 _count, const glm::vec4* _val) const noexcept
{
	const s32 uniformLocation = findUniformLocation(_name);
	if (uniformLocation != k_locationUndefined)
	{
		glUniform4fv(uniformLocation, _count, reinterpret_cast<const float*>(_val));
	}
}

//-----------------------------------------------------------------------------

s32 Shader::findUniformLocation(const std::string& _name) const
{
	s32 location = k_locationUndefined;

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
	u32 shader = glCreateShader(_type);

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
			LOG_INFO("[Shader] Shader compile error message: {}", message);

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
			LOG_INFO("[Shader] Shading program link error message: {}", message);

			delete[] message;
		}

		return false;
	}

	return true;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
