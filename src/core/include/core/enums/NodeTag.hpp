#pragma once

#include "utils/Assert.hpp"
#include "utils/EnumUtils.hpp"

//-----------------------------------------------------------------------------

namespace enums {

//-----------------------------------------------------------------------------

enum class NodeTag
{
	NonTagged,
	Red,
	Orange,
	Yellow,
	Green,
	Blue,
	Purple,
	Gray,

	Count
};

//-----------------------------------------------------------------------------

constexpr std::string_view toString(NodeTag _tag)
{
	constexpr int lastVerNodeTagsCount = 8;
	static_assert(static_cast<int>(NodeTag::Count) == lastVerNodeTagsCount);

	switch (_tag)
	{
		ENUM_TO_STRING_CASE(NodeTag, NonTagged);
		ENUM_TO_STRING_CASE(NodeTag, Red);
		ENUM_TO_STRING_CASE(NodeTag, Orange);
		ENUM_TO_STRING_CASE(NodeTag, Yellow);
		ENUM_TO_STRING_CASE(NodeTag, Blue);
		ENUM_TO_STRING_CASE(NodeTag, Purple);
		ENUM_TO_STRING_CASE(NodeTag, Gray);

		default:
			ASSERT_FALSE("Unhandled case");
	}
}

//-----------------------------------------------------------------------------

} // namespace enums

//-----------------------------------------------------------------------------
