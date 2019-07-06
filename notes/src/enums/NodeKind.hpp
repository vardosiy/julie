#ifndef __NODE_KIND_HPP__
#define __NODE_KIND_HPP__

//-----------------------------------------------------------------------------

#include "utils/EnumUtils.hpp"

#include <string_view>

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

	constexpr static std::string_view toString(Enum _tag);
	constexpr static Enum fromString(std::string_view _str);
};

//-----------------------------------------------------------------------------

constexpr inline std::string_view NodeKind::toString(Enum _tag)
{
	constexpr int lastVerNodeKindsCount{ 2 };

	static_assert(
		static_cast<int>(NodeKind::Count) == lastVerNodeKindsCount,
		"Update NodeKind::toString converter!"
	);

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
	return utils::fromString<NodeKind>(_str);
}

//-----------------------------------------------------------------------------

} // namespace enums

//-----------------------------------------------------------------------------

#endif // __NODE_KIND_HPP__
