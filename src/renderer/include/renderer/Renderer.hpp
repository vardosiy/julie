#pragma once

#include "renderer/Types.hpp"

#include <glm/vec4.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

enum class PolygonMode
{
	Fill,
	Line
};

class Renderer
{
public:
	static void setFrontPolygonsMode(PolygonMode _mode) noexcept;
	static void setBackPolygonsMode(PolygonMode _mode) noexcept;

	static void setClearColor(const glm::vec4& _color) noexcept;

private:
	static s32 polygonModeToGlValue(PolygonMode _mode) noexcept;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
