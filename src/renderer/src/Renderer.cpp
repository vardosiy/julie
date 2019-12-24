#include "renderer/Renderer.hpp"

#include "renderer/managers/SceneManager.hpp"
#include "renderer/scene/Object.hpp"

#include <glad/glad.h>

#include <cassert>

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
			assert(0);
	}
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
