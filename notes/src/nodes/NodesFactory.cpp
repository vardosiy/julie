#include "Pch.hpp"

#include "NodesFactory.hpp"

#include "Note.hpp"
#include "NotesFolder.hpp"

//-----------------------------------------------------------------------------

NotePtr NodesFactory::createNote(std::string_view _text)
{
	return std::make_unique<Note>(_text);
}

//-----------------------------------------------------------------------------

NotesFolderPtr NodesFactory::createNotesFolder(std::string_view _name)
{
	return std::make_unique<NotesFolder>(_name);
}

//-----------------------------------------------------------------------------
