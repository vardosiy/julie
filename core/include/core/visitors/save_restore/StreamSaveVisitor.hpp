#pragma once

#include "core/visitors/Visitor.hpp"
#include "utils/save_restore/StreamWriter.hpp"

//-----------------------------------------------------------------------------

namespace visitors::save_restore {

//-----------------------------------------------------------------------------

class StreamSaveVisitor : public Visitor, utils::save_restore::StreamWriter
{
public:
	explicit StreamSaveVisitor(std::ostream & _stream) noexcept;

	void operator() (nodes::Note & _note) override;
	void operator() (nodes::NotesFolder & _notesFolder) override;

private:
	void saveCommon(nodes::HierarchyNode & _node);
};

//-----------------------------------------------------------------------------

} // namespace visitors::save_restore

//-----------------------------------------------------------------------------
