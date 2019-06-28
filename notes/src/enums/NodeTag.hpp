#ifndef __NODE_TAG_HPP__
#define __NODE_TAG_HPP__

//-----------------------------------------------------------------------------

#include "utils/StringConverterUtils.hpp"

#include <string_view>
#include <cassert>

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

		Count,
	};

	static std::string_view toString(Enum _tag);

	static Enum fromString(std::string_view _str);
};

//-----------------------------------------------------------------------------

inline std::string_view NodeTag::toString(Enum _tag)
{
	constexpr int lastVerNodeTagsCount = 8;
	static_assert(
		static_cast<int>(NodeTag::Count) == lastVerNodeTagsCount,
		"Update NodeTag::toString converter!"
	);

	switch (_tag)
	{
		TO_STRING_CASE(NonTaged);
		TO_STRING_CASE(Red);
		TO_STRING_CASE(Orange);
		TO_STRING_CASE(Yellow);
		TO_STRING_CASE(Blue);
		TO_STRING_CASE(Purple);
		TO_STRING_CASE(Gray);

		default:
			assert(0);
	}
}

//-----------------------------------------------------------------------------

inline NodeTag::Enum NodeTag::fromString(std::string_view _str)
{
	return utils::enumFromString<NodeTag>(_str);
}

//-----------------------------------------------------------------------------

#endif // __NODE_TAG_HPP__
