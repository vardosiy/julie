#ifndef __VISITOR_HPP__
#define __VISITOR_HPP__

//-----------------------------------------------------------------------------

#include "nodes/NodesFwd.hpp"

//-----------------------------------------------------------------------------

class Visitor
{
public:
	virtual void operator() (nodes::Note & _note) = 0;
	virtual void operator() (nodes::NotesFolder & _notesFolder) = 0;
};

//-----------------------------------------------------------------------------

#endif // __VISITOR_HPP__
