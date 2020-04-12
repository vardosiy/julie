#pragma once

#include "renderer/Types.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

enum class TextureTiling;
enum class TextureFiltering;

float	tilingToGlValue(TextureTiling _tiling) noexcept;
s32		filteringToGlValue(TextureFiltering _mode) noexcept;

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
