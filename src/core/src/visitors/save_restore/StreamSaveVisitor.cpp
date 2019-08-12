#include "core/visitors/save_restore/StreamSaveVisitor.hpp"

#include "core/nodes/Note.hpp"
#include "core/nodes/NotesFolder.hpp"

//-----------------------------------------------------------------------------

namespace visitors::save_restore {

//-----------------------------------------------------------------------------

StreamSaveVisitor::StreamSaveVisitor(std::ostream & _stream) noexcept
	: StreamWriter(_stream)
{
}

//-----------------------------------------------------------------------------

void StreamSaveVisitor::operator() (nodes::Note & _note)
{
	saveCommon(_note);

	write(_note.getText());
}

//-----------------------------------------------------------------------------

void StreamSaveVisitor::operator() (nodes::NotesFolder & _notesFolder)
{
	saveCommon(_notesFolder);

	write(_notesFolder.getName());
	write(_notesFolder.getChildrenCount());

	_notesFolder.forEachChildNode(
		[this](nodes::HierarchyNode & _node)
		{
			_node.accept(*this);
		}
	);
}

//-----------------------------------------------------------------------------

void StreamSaveVisitor::saveCommon(nodes::HierarchyNode & _node)
{
	write(_node.getKind());
	write(_node.getTag());
}

//-----------------------------------------------------------------------------

} // namespace visitors::save_restore

//-----------------------------------------------------------------------------
