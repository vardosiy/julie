#pragma once

#include "renderer/common/Types.hpp"

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
	static void setFrontPolygonsMode(PolygonMode _mode);
	static void setBackPolygonsMode(PolygonMode _mode);

private:
	static s32 polygonModeToGlValue(PolygonMode _mode);
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
