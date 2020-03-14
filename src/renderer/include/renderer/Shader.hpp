#pragma once

#include "renderer/Types.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <boost/noncopyable.hpp>

#include <memory>
#include <string_view>
#include <unordered_map>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Model;

class Shader : boost::noncopyable
{
public:
	static std::unique_ptr<Shader> create(std::string_view _vsSource, std::string_view _fsSource);

	static void draw(const Model& _model);

public:
	~Shader();

	void bind() const noexcept;

	bool hasUniform(const std::string& _name) const noexcept;

	void setUniform(const std::string& _name, s32 _val) const;
	void setUniform(const std::string& _name, float _val) const;
	void setUniform(const std::string& _name, const glm::vec2& _val) const;
	void setUniform(const std::string& _name, const glm::vec3& _val) const;
	void setUniform(const std::string& _name, const glm::vec4& _val) const;
	void setUniform(const std::string& _name, const glm::mat4& _val) const;

	void setUniform(const std::string& _name, u32 _count, const s32* _val) const;
	void setUniform(const std::string& _name, u32 _count, const glm::vec3* _val) const;
	void setUniform(const std::string& _name, u32 _count, const glm::vec4* _val) const;

private:
	Shader() = default;

	s32 getUniformLocation(const std::string& _name) const;

	static u32 loadShader(u32 _type, std::string_view _source) noexcept;
	static u32 loadProgram(u32 _vsId, u32 _fsId) noexcept;
	static bool checkShaderCompilationSucceded(u32 _shaderId) noexcept;
	static bool checkProgramLinkageSucceded(u32 _programId) noexcept;

private:
	using UniformsCache = std::unordered_map<std::string, s32>;
	mutable UniformsCache m_uniformLocationsCache;

	u32 m_program;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
