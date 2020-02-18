#include "renderer/Renderer.hpp"

#include "utils/Assert.hpp"

#include <glad/glad.h>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

void Renderer::setFrontPolygonsMode(PolygonMode _mode) noexcept
{
	glPolygonMode(GL_FRONT, polygonModeToGlValue(_mode));
}

//-----------------------------------------------------------------------------

void Renderer::setBackPolygonsMode(PolygonMode _mode) noexcept
{
	glPolygonMode(GL_BACK, polygonModeToGlValue(_mode));
}

//-----------------------------------------------------------------------------

void Renderer::setClearColor(const glm::vec4& _color) noexcept
{
	glClearColor(_color.r, _color.g, _color.b, _color.a);
}

//-----------------------------------------------------------------------------

s32 Renderer::polygonModeToGlValue(PolygonMode _mode) noexcept
{
	switch (_mode)
	{
		case PolygonMode::Fill: return GL_FILL;
		case PolygonMode::Line: return GL_LINE;
	}

	ASSERT(0);
	return 0;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
