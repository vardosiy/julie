#pragma once

#include <memory>

//-----------------------------------------------------------------------------

namespace nodes {

//-----------------------------------------------------------------------------

class Note;
class NotesFolder;
class HierarchyNode;

using NotePtr			= std::unique_ptr<Note>;
using NotesFolderPtr	= std::unique_ptr<NotesFolder>;
using HierarchyNodePtr	= std::unique_ptr<HierarchyNode>;

//-----------------------------------------------------------------------------

} // namespace nodes

//-----------------------------------------------------------------------------
