#ifndef __VISITOR_HPP__
#define __VISITOR_HPP__

//-----------------------------------------------------------------------------

#include "core/nodes/NodesFwd.hpp"

//-----------------------------------------------------------------------------

namespace visitors {

//-----------------------------------------------------------------------------

class Visitor
{
public:
	virtual void operator() (nodes::Note & _note) = 0;
	virtual void operator() (nodes::NotesFolder & _notesFolder) = 0;
};

//-----------------------------------------------------------------------------

} // namespace visitors

//-----------------------------------------------------------------------------

#endif // __VISITOR_HPP__
