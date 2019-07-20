#pragma once

#include "core/nodes/NodesFwd.hpp"

//-----------------------------------------------------------------------------

namespace visitors {

//-----------------------------------------------------------------------------

class Visitor
{
public:
	virtual ~Visitor() noexcept = default;

	virtual void operator() (nodes::Note & _note) = 0;
	virtual void operator() (nodes::NotesFolder & _notesFolder) = 0;
};

//-----------------------------------------------------------------------------

} // namespace visitors

//-----------------------------------------------------------------------------
