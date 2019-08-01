#pragma once

#include "utils/Assert.hpp"
#include "utils/EnumUtils.hpp"

//-----------------------------------------------------------------------------

namespace enums {

//-----------------------------------------------------------------------------

class NodeTag
{
public:
	enum Enum
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

public:
	static constexpr std::string_view toString(Enum _tag);
	static constexpr Enum fromString(std::string_view _str);
};

//-----------------------------------------------------------------------------

constexpr std::string_view NodeTag::toString(Enum _tag)
{
	constexpr int lastVerNodeTagsCount{ 8 };
	static_assert(static_cast<int>(Count) == lastVerNodeTagsCount);

	switch (_tag)
	{
		ENUM_TO_STRING_CASE(NonTagged);
		ENUM_TO_STRING_CASE(Red);
		ENUM_TO_STRING_CASE(Orange);
		ENUM_TO_STRING_CASE(Yellow);
		ENUM_TO_STRING_CASE(Blue);
		ENUM_TO_STRING_CASE(Purple);
		ENUM_TO_STRING_CASE(Gray);

		default:
			ASSERT_FALSE("Unhandled case");
	}
}

//-----------------------------------------------------------------------------

constexpr NodeTag::Enum NodeTag::fromString(std::string_view _str)
{
	return utils::enums::fromString<NodeTag>(_str);
}

//-----------------------------------------------------------------------------

} // namespace enums

//-----------------------------------------------------------------------------
