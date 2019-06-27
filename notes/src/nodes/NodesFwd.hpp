#ifndef __ENTITIES_FWD_HPP__
#define __ENTITIES_FWD_HPP__

//-----------------------------------------------------------------------------

#include <memory>

//-----------------------------------------------------------------------------

class Note;
class NotesFolder;
class HierarchyNode;

using NotePtr = std::unique_ptr<Note>;
using NotesFolderPtr = std::unique_ptr<NotesFolder>;
using HierarchyNodePtr = std::unique_ptr<HierarchyNode>;

//-----------------------------------------------------------------------------

#endif // __ENTITIES_FWD_HPP__
