#pragma once

#include "utils/Assert.hpp"
#include "utils/EnumUtils.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

enum class TextureFilteringMode
{
	Nearest,
	Linear,
	LinearMipmapLinear,

	Count
};

//-----------------------------------------------------------------------------

constexpr std::string_view toString(TextureFilteringMode _tiling)
{
	constexpr int lastVerNodeKindsCount{ 3 };
	static_assert(static_cast<int>(TextureFilteringMode::Count) == lastVerNodeKindsCount);

	switch (_tiling)
	{
		ENUM_TO_STRING_CASE(TextureFilteringMode, Nearest);
		ENUM_TO_STRING_CASE(TextureFilteringMode, Linear);
		ENUM_TO_STRING_CASE(TextureFilteringMode, LinearMipmapLinear);

		default:
			ASSERT(false, "Unhandled case");
	}

	return "";
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------

ENUM_NAME_GETTER(jl::TextureFilteringMode)

//-----------------------------------------------------------------------------
