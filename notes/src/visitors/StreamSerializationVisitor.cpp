#include "Pch.hpp"

#include "StreamSerializationVisitor.hpp"

#include "nodes/Note.hpp"
#include "nodes/NotesFolder.hpp"

//-----------------------------------------------------------------------------

StreamSerializationVisitor::StreamSerializationVisitor(std::ostream & _stream) noexcept
	: m_stream{ _stream }
{
}

//-----------------------------------------------------------------------------

void StreamSerializationVisitor::operator() (nodes::Note & _note)
{
	serializeNodeKind(_note);

	m_stream
		<< _note.getTag()
		<< _note.getText();
}

//-----------------------------------------------------------------------------

void StreamSerializationVisitor::operator() (nodes::NotesFolder & _notesFolder)
{
	serializeNodeKind(_notesFolder);

	m_stream
		<< _notesFolder.getName()
		<< _notesFolder.getTag()
		<< _notesFolder.getChildNodesCount();

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
	m_stream << static_cast<int>(_node.getKind());
}

//-----------------------------------------------------------------------------
