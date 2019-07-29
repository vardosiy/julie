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

	void operator() (nodes::Note & _note) override;
	void operator() (nodes::NotesFolder & _notesFolder) override;

private:
	void restoreCommon(nodes::HierarchyNode & _hierarchyNode);

private:
	nodes::HierarchyNodePtr deserializeNode();
};

//-----------------------------------------------------------------------------

} // namespace visitors::save_restore

//-----------------------------------------------------------------------------
