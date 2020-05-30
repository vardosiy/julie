#pragma once

#include "renderer/Types.hpp"

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <memory>
#include <string>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Model;
class Shader;
class VertexArray;

class Renderer
{
//-----------------------------------------------------------------------------
public:
	enum class PolygonMode
	{
		Fill,
		Line
	};

//-----------------------------------------------------------------------------
	static void init();
	static void shutdown();

	static void draw(const Model& _model) noexcept;
	static void draw(const boxf& _box, const glm::vec4& _color, const glm::mat4& _transform) noexcept;

	static void setClearColor(const glm::vec4& _color) noexcept;

	static void setFrontPolygonsMode(PolygonMode _mode) noexcept;
	static void setBackPolygonsMode(PolygonMode _mode) noexcept;

//-----------------------------------------------------------------------------
private:
	static s32 polygonModeToGlValue(PolygonMode _mode) noexcept;

//-----------------------------------------------------------------------------
	static std::unique_ptr<Shader> s_shader;
	static std::unique_ptr<VertexArray> s_vertexArray;

	static const std::string k_primitivesShaderVsSource;
	static const std::string k_primitivesShaderFsSource;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
