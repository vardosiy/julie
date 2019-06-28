#include "Pch.hpp"

#include "StreamSerializationVisitor.hpp"

#include "nodes/Note.hpp"
#include "nodes/NotesFolder.hpp"

//-----------------------------------------------------------------------------

StreamSerializationVisitor::StreamSerializationVisitor(std::ostream & _stream) noexcept
	: m_stream(_stream)
{
}

//-----------------------------------------------------------------------------

void StreamSerializationVisitor::visit(Note & _note)
{
	serializeNodeKind(_note);

	m_stream
		<< _note.getTag()
		<< _note.getText();
}

//-----------------------------------------------------------------------------

void StreamSerializationVisitor::visit(NotesFolder & _notesFolder)
{
	serializeNodeKind(_notesFolder);

	m_stream
		<< _notesFolder.getName()
		<< _notesFolder.getTag()
		<< _notesFolder.getChildNodesCount();

	_notesFolder.forEachChildNode(
		[this](HierarchyNode & _node)
		{
			_node.accept(*this);
		}
	);
}

//-----------------------------------------------------------------------------

void StreamSerializationVisitor::serializeNodeKind(HierarchyNode & _node)
{
	m_stream << static_cast<int>(_node.getKind());
}

//-----------------------------------------------------------------------------
