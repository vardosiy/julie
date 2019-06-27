#ifndef __ENTITIES_FWD_HPP__
#define __ENTITIES_FWD_HPP__

//-----------------------------------------------------------------------------

#include <memory>

//-----------------------------------------------------------------------------

class HierarchyItem;
class Note;
class NotesFolder;

using NotePtr = std::unique_ptr<Note>;
using NotesFoldersPtr = std::unique_ptr<NotesFolder>;
using HierarchyItemPtr = std::unique_ptr<HierarchyItem>;

//-----------------------------------------------------------------------------

#endif // __ENTITIES_FWD_HPP__
