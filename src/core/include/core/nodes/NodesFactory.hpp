#pragma once

#include "core/nodes/NodesFwd.hpp"

#include <string_view>

//-----------------------------------------------------------------------------

namespace nodes {

//-----------------------------------------------------------------------------

class NodesFactory
{
public:
	static NotePtr createNote(std::string_view _text) noexcept;
	static NotesFolderPtr createNotesFolder(std::string_view _name) noexcept;
};

//-----------------------------------------------------------------------------

} // namespace nodes

//-----------------------------------------------------------------------------
