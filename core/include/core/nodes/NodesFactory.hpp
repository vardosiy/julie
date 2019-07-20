#pragma once

#include "core/nodes/NodesFwd.hpp"

#include <boost/noncopyable.hpp>

//-----------------------------------------------------------------------------

namespace nodes {

//-----------------------------------------------------------------------------

class NodesFactory : boost::noncopyable
{
public:
	static NotePtr createNote(std::string_view _text) noexcept;
	static NotesFolderPtr createNotesFolder(std::string_view _name) noexcept;
};

//-----------------------------------------------------------------------------

} // namespace nodes

//-----------------------------------------------------------------------------
