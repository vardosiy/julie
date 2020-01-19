#pragma once

#include "renderer/Types.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <boost/noncopyable.hpp>

#include <vector>
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
	static std::unique_ptr<Shader> create(std::string_view _vsPath, std::string_view _fsPath);

	static void draw(const Model& _model);

public:
	~Shader();

	void bind() const noexcept;

	bool hasUniform(const std::string& _name) const noexcept;

	void setUniformValue(const std::string& _name, s32 _val) const;
	void setUniformValue(const std::string& _name, float _val) const;
	void setUniformValue(const std::string& _name, const glm::vec2& _val) const;
	void setUniformValue(const std::string& _name, const glm::vec3& _val) const;
	void setUniformValue(const std::string& _name, const glm::vec4& _val) const;
	void setUniformValue(const std::string& _name, const glm::mat4& _val) const;

	void setUniformValue(const std::string& _name, u32 _count, const s32* _val) const;
	void setUniformValue(const std::string& _name, u32 _count, const glm::vec3* _val) const;
	void setUniformValue(const std::string& _name, u32 _count, const glm::vec4* _val) const;

private:
	Shader() = default;

	s32 getUniformLocation(const std::string& _name) const;

private:
	using UniformsCache = std::unordered_map<std::string, s32>;
	mutable UniformsCache m_uniformLocationsCache;

	u32 m_program;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
