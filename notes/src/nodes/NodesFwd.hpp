#ifndef __NODES_FWD_HPP__
#define __NODES_FWD_HPP__

//-----------------------------------------------------------------------------

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

#endif // __NODES_FWD_HPP__
