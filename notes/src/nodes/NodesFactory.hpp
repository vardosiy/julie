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
	static NotePtr createNote(std::string_view _text) noexcept;
	static NotesFolderPtr createNotesFolder(std::string_view _name) noexcept;
};

//-----------------------------------------------------------------------------

} // namespace nodes

//-----------------------------------------------------------------------------

#endif // __NODES_FACTORY_HPP__
