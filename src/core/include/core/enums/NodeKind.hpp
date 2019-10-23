#pragma once

#include "utils/Assert.hpp"
#include "utils/EnumUtils.hpp"

//-----------------------------------------------------------------------------

namespace enums {

//-----------------------------------------------------------------------------

enum class NodeKind
{
	Note,
	NotesFolder,

	Count
};

//-----------------------------------------------------------------------------

ENUM_NAME_GETTER(NodeKind)

//-----------------------------------------------------------------------------

constexpr std::string_view toString(NodeKind _kind)
{
	constexpr int lastVerNodeKindsCount{ 2 };
	static_assert(static_cast<int>(NodeKind::Count) == lastVerNodeKindsCount);

	switch (_kind)
	{
		ENUM_TO_STRING_CASE(NodeKind, Note);
		ENUM_TO_STRING_CASE(NodeKind, NotesFolder);

		default:
			ASSERT(false, "Unhandled case");
	}

	return "";
}

//-----------------------------------------------------------------------------

} // namespace enums

//-----------------------------------------------------------------------------
