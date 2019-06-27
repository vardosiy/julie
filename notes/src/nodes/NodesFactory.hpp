#ifndef __NODES_FACTORY_HPP__
#define __NODES_FACTORY_HPP__

//-----------------------------------------------------------------------------

#include "NodesFwd.hpp"

//-----------------------------------------------------------------------------

class NodesFactory : boost::noncopyable
{
public:
	NotePtr createNote(std::string_view _text);
	NotesFolderPtr createNotesFolder(std::string_view _name);
};

//-----------------------------------------------------------------------------

#endif // __NODES_FACTORY_HPP__
