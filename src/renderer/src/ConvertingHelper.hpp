#pragma once

#include "renderer/Types.hpp"
#include "renderer/TextureTiling.hpp"
#include "renderer/TextureFilteringMode.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

float	tilingToGlValue(TextureTiling _tiling) noexcept;
s32		filteringModeToGlValue(TextureFilteringMode _mode) noexcept;

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
