#pragma once

#include "utils/Assert.hpp"
#include "utils/EnumUtils.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

enum class TextureTiling
{
	ClampToEdge,
	Repeat,

	Count
};

//-----------------------------------------------------------------------------

constexpr std::string_view toString(TextureTiling _tiling)
{
	constexpr int lastVerNodeKindsCount{ 2 };
	static_assert(static_cast<int>(TextureTiling::Count) == lastVerNodeKindsCount);

	switch (_tiling)
	{
		ENUM_TO_STRING_CASE(TextureTiling, ClampToEdge);
		ENUM_TO_STRING_CASE(TextureTiling, Repeat);

		default:
			ASSERT(false, "Unhandled case");
	}

	return "";
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------

ENUM_NAME_GETTER(jl::TextureTiling)

//-----------------------------------------------------------------------------
