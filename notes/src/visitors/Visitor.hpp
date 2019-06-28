#ifndef __VISITOR_HPP__
#define __VISITOR_HPP__

//-----------------------------------------------------------------------------

#include "nodes/NodesFwd.hpp"

//-----------------------------------------------------------------------------

class Visitor
{
public:
	virtual void visit(Note & _note) = 0;
	virtual void visit(NotesFolder & _notesFolder) = 0;
};

//-----------------------------------------------------------------------------

#endif // __VISITOR_HPP__
