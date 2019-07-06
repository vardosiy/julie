#ifndef __NODE_TAG_HPP__
#define __NODE_TAG_HPP__

//-----------------------------------------------------------------------------

#include "utils/EnumUtils.hpp"

#include <string_view>

//-----------------------------------------------------------------------------

namespace enums {

//-----------------------------------------------------------------------------

class NodeTag
{
public:
	enum Enum
	{
		NonTaged,
		Red,
		Orange,
		Yellow,
		Green,
		Blue,
		Purple,
		Gray,

		Count
	};

	constexpr static std::string_view toString(Enum _tag);
	constexpr static Enum fromString(std::string_view _str);
};

//-----------------------------------------------------------------------------

constexpr inline std::string_view NodeTag::toString(Enum _tag)
{
	constexpr int lastVerNodeTagsCount{ 8 };

	static_assert(
		static_cast<int>(NodeTag::Count) == lastVerNodeTagsCount,
		"Update NodeTag::toString converter!"
	);

	switch (_tag)
	{
		ENUM_TO_STRING_CASE(NonTaged);
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

constexpr inline NodeTag::Enum NodeTag::fromString(std::string_view _str)
{
	return utils::fromString<NodeTag>(_str);
}

//-----------------------------------------------------------------------------

} // namespace enums

//-----------------------------------------------------------------------------

#endif // __NODE_TAG_HPP__
