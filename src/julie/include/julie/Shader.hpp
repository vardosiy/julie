#pragma once

#include "julie/core/Types.hpp"

#include "utils/Noncopyable.hpp"

#include <glm/glm.hpp>

#include <memory>
#include <string_view>
#include <unordered_map>

//-----------------------------------------------------------------------------
namespace jl {
//-----------------------------------------------------------------------------

class Model;

class Shader : utils::Noncopyable
{
//-----------------------------------------------------------------------------
public:
	static std::unique_ptr<Shader> loadFromFile(std::string_view _filePath);
	static std::unique_ptr<Shader> loadFromFiles(std::string_view _vsPath, std::string_view _fsPath);
	static std::unique_ptr<Shader> create(std::string_view _vsSource, std::string_view _fsSource);

//-----------------------------------------------------------------------------
	~Shader();

	void bind() const noexcept;

//-----------------------------------------------------------------------------
	bool hasUniform(const std::string& _name) const noexcept;

	void setUniform(const std::string& _name, s32 _val) const noexcept;
	void setUniform(const std::string& _name, float _val) const noexcept;
	void setUniform(const std::string& _name, const glm::vec2& _val) const noexcept;
	void setUniform(const std::string& _name, const glm::vec3& _val) const noexcept;
	void setUniform(const std::string& _name, const glm::vec4& _val) const noexcept;
	void setUniform(const std::string& _name, const glm::mat4& _val) const noexcept;

	void setUniform(const std::string& _name, u32 _count, const s32* _val) const noexcept;
	void setUniform(const std::string& _name, u32 _count, const glm::vec3* _val) const noexcept;
	void setUniform(const std::string& _name, u32 _count, const glm::vec4* _val) const noexcept;

//-----------------------------------------------------------------------------
private:
	Shader(u32 _programId);

	s32 findUniformLocation(const std::string& _name) const;

	static u32 loadShader(u32 _type, std::string_view _source) noexcept;
	static u32 loadProgram(u32 _vsId, u32 _fsId) noexcept;
	static bool checkShaderCompilationSucceded(u32 _shaderId) noexcept;
	static bool checkProgramLinkageSucceded(u32 _programId) noexcept;

//-----------------------------------------------------------------------------
	using UniformsCache = std::unordered_map<std::string, s32>;
	mutable UniformsCache m_uniformLocationsCache;

	u32 m_programId;

	static constexpr s32 k_locationUndefined = -1;
};

//-----------------------------------------------------------------------------
} // namespace jl
//-----------------------------------------------------------------------------
