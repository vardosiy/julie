#include "Pch.hpp"

#include "StreamSerializationVisitor.hpp"

#include "nodes/Note.hpp"
#include "nodes/NotesFolder.hpp"

//-----------------------------------------------------------------------------

namespace visitors {

//-----------------------------------------------------------------------------

StreamSerializationVisitor::StreamSerializationVisitor(std::ostream & _stream) noexcept
	: StreamWritingHelper{ _stream }
{
}

//-----------------------------------------------------------------------------

void StreamSerializationVisitor::operator() (nodes::Note & _note)
{
	serializeNodeKind(_note);

	write(_note.getTag());
	write(_note.getText());
}

//-----------------------------------------------------------------------------

void StreamSerializationVisitor::operator() (nodes::NotesFolder & _notesFolder)
{
	serializeNodeKind(_notesFolder);

	write(_notesFolder.getTag());
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

void StreamSerializationVisitor::serializeNodeKind(nodes::HierarchyNode & _node)
{
	write(_node.getKind());
}

//-----------------------------------------------------------------------------

} // namespace visitors

//-----------------------------------------------------------------------------
