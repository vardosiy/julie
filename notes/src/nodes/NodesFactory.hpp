#ifndef __NODES_FACTORY_HPP__
#define __NODES_FACTORY_HPP__

//-----------------------------------------------------------------------------

#include "NodesFwd.hpp"

//-----------------------------------------------------------------------------

namespace nodes {

//-----------------------------------------------------------------------------

class NodesFactory : boost::noncopyable
{
public:
	NotePtr createNote(std::string_view _text);
	NotesFolderPtr createNotesFolder(std::string_view _name);
};

//-----------------------------------------------------------------------------

} // namespace nodes

//-----------------------------------------------------------------------------

#endif // __NODES_FACTORY_HPP__
