#include "core/nodes/NodesFactory.hpp"
#include "core/nodes/Note.hpp"
#include "core/nodes/NotesFolder.hpp"

//-----------------------------------------------------------------------------

namespace nodes {

//-----------------------------------------------------------------------------

NotePtr NodesFactory::createNote(std::string_view _text) noexcept
{
	return std::make_unique<Note>(_text);
}

//-----------------------------------------------------------------------------

NotesFolderPtr NodesFactory::createNotesFolder(std::string_view _name) noexcept
{
	return std::make_unique<NotesFolder>(_name);
}

//-----------------------------------------------------------------------------

} // namespace nodes

//-----------------------------------------------------------------------------
