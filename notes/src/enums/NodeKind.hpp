#ifndef __NODE_KIND_HPP__
#define __NODE_KIND_HPP__

//-----------------------------------------------------------------------------

#include "utils/StringConverterUtils.hpp"

#include <string_view>
#include <cassert>

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

	static std::string_view toString(Enum _tag);

	static Enum fromString(std::string_view _str);
};

//-----------------------------------------------------------------------------

inline std::string_view NodeKind::toString(Enum _tag)
{
	constexpr int lastVerNodeKindsCount = 2;
	static_assert(
		static_cast<int>(NodeKind::Count) == lastVerNodeKindsCount,
		"Update NodeKind::toString converter!"
	);

	switch (_tag)
	{
		TO_STRING_CASE(Note);
		TO_STRING_CASE(NotesFolder);

		default:
			assert(0);
	}
}

//-----------------------------------------------------------------------------

inline NodeKind::Enum NodeKind::fromString(std::string_view _str)
{
	return utils::enumFromString<NodeKind>(_str);
}

//-----------------------------------------------------------------------------

#endif // __NODE_KIND_HPP__
