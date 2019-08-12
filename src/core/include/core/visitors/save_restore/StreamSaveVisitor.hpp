#pragma once

#include "core/visitors/Visitor.hpp"
#include "utils/save_restore/StreamWriter.hpp"

//-----------------------------------------------------------------------------

namespace visitors::sr {

//-----------------------------------------------------------------------------

class StreamSaveVisitor : public Visitor, utils::sr::StreamWriter
{
public:
	explicit StreamSaveVisitor(std::ostream & _stream) noexcept;

	void operator() (nodes::Note & _note) override;
	void operator() (nodes::NotesFolder & _notesFolder) override;

private:
	void saveCommon(nodes::HierarchyNode & _node);
};

//-----------------------------------------------------------------------------

} // namespace visitors::sr

//-----------------------------------------------------------------------------
