#pragma once

#include "utils/Assert.hpp"
#include "utils/EnumUtils.hpp"

//-----------------------------------------------------------------------------

namespace enums {

//-----------------------------------------------------------------------------

class NodeKind
{
public:
	enum Enum
	{
		Note,
		NotesFolder,

		Count
	};

public:
	static constexpr std::string_view toString(Enum _tag);
	static constexpr Enum fromString(std::string_view _str);
};

//-----------------------------------------------------------------------------

constexpr inline std::string_view NodeKind::toString(Enum _tag)
{
	constexpr int lastVerNodeKindsCount{ 2 };
	static_assert(static_cast<int>(NodeKind::Count) == lastVerNodeKindsCount);

	switch (_tag)
	{
		ENUM_TO_STRING_CASE(Note);
		ENUM_TO_STRING_CASE(NotesFolder);

		default:
		ASSERT_FALSE("Unhandled case");
	}
}

//-----------------------------------------------------------------------------

constexpr inline NodeKind::Enum NodeKind::fromString(std::string_view _str)
{
	return utils::enums::fromString<NodeKind>(_str);
}

//-----------------------------------------------------------------------------

} // namespace enums

//-----------------------------------------------------------------------------
