#pragma once

#include "renderer/Types.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

enum class TextureTiling;
enum class TextureFilteringMode;

float	tilingToGlValue(TextureTiling _tiling) noexcept;
s32		filteringModeToGlValue(TextureFilteringMode _mode) noexcept;

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
