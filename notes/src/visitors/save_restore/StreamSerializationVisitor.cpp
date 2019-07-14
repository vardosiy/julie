#include "Pch.hpp"

#include "StreamSerializationVisitor.hpp"

#include "nodes/Note.hpp"
#include "nodes/NotesFolder.hpp"

//-----------------------------------------------------------------------------

namespace visitors::save_restore {

//-----------------------------------------------------------------------------

StreamSerializationVisitor::StreamSerializationVisitor(std::ostream & _stream) noexcept
	: StreamWriter{ _stream }
{
}

//-----------------------------------------------------------------------------

void StreamSerializationVisitor::operator() (nodes::Note & _note)
{
	serializeCommon(_note);

	write(_note.getText());
}

//-----------------------------------------------------------------------------

void StreamSerializationVisitor::operator() (nodes::NotesFolder & _notesFolder)
{
	serializeCommon(_notesFolder);

	write(_notesFolder.getName());
	write(_notesFolder.getChildNodesCount());

	_notesFolder.forEachChildNode(
		[this](nodes::HierarchyNode & _node)
		{
			_node.accept(*this);
		}
	);
}

//-----------------------------------------------------------------------------

void StreamSerializationVisitor::serializeCommon(nodes::HierarchyNode & _node)
{
	write(_node.getKind());
	write(_node.getTag());
}

//-----------------------------------------------------------------------------

} // namespace visitors

//-----------------------------------------------------------------------------
