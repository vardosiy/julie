#include "renderer/Renderer.hpp"

#include "utils/Assert.hpp"

#include <glad/glad.h>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

void Renderer::setFrontPolygonsMode(PolygonMode _mode)
{
	glPolygonMode(GL_FRONT, polygonModeToGlValue(_mode));
}

//-----------------------------------------------------------------------------

void Renderer::setBackPolygonsMode(PolygonMode _mode)
{
	glPolygonMode(GL_BACK, polygonModeToGlValue(_mode));
}

//-----------------------------------------------------------------------------

s32 Renderer::polygonModeToGlValue(PolygonMode _mode)
{
	switch (_mode)
	{
		case jl::PolygonMode::Fill: return GL_FILL;
		case jl::PolygonMode::Line: return GL_LINE;

		default:
			ASSERT(0);
	}

	return 0;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
