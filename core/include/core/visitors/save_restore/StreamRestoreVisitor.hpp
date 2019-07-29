#pragma once

#include "core/visitors/Visitor.hpp"
#include "utils/save_restore/StreamReader.hpp"

//-----------------------------------------------------------------------------

namespace visitors::save_restore {

//-----------------------------------------------------------------------------

class StreamRestoreVisitor : public Visitor, utils::save_restore::StreamReader
{
public:
	explicit StreamRestoreVisitor(std::istream & _stream) noexcept;

	nodes::HierarchyNodePtr run();

	void operator() (nodes::Note & _note) override;
	void operator() (nodes::NotesFolder & _notesFolder) override;

private:
	nodes::HierarchyNodePtr deserializeNode();
};

//-----------------------------------------------------------------------------

} // namespace visitors::save_restore

//-----------------------------------------------------------------------------
