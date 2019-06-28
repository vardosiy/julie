#include "Pch.hpp"

#include "StreamDeserializationVisitor.hpp"

#include "nodes/HierarchyNode.hpp"
#include "nodes/Note.hpp"
#include "nodes/NotesFolder.hpp"

#include "nodes/NodesFactory.hpp"

//-----------------------------------------------------------------------------

StreamDeserializationVisitor::StreamDeserializationVisitor(std::istream & _stream) noexcept
	: m_stream(_stream)
{
}

//-----------------------------------------------------------------------------

NotesFolderPtr StreamDeserializationVisitor::run()
{
	HierarchyNodePtr rootNode = deserializeNode();
	assert(rootNode->getKind() == NodeKind::NotesFolder);

	return NotesFolderPtr(dynamic_cast<NotesFolder *>(rootNode.release()));
}

//-----------------------------------------------------------------------------

void StreamDeserializationVisitor::visit(Note & _note)
{
	int tag;
	std::string text;

	m_stream
		>> tag
		>> text;

	_note.setTag(static_cast<NodeTag::Enum>(tag));
	_note.setText(text);
}

//-----------------------------------------------------------------------------

void StreamDeserializationVisitor::visit(NotesFolder & _notesFolder)
{
	std::string folderName;
	int tag;
	int childNodesCount;

	m_stream
		>> folderName
		>> tag
		>> childNodesCount;

	_notesFolder.setName(folderName);
	_notesFolder.setTag(static_cast<NodeTag::Enum>(tag));

	for (int i{ 0 }; i < childNodesCount; ++i)
	{
		HierarchyNodePtr node = deserializeNode();
		_notesFolder.addChildNode(std::move(node));
	}
}

//-----------------------------------------------------------------------------

HierarchyNodePtr StreamDeserializationVisitor::deserializeNode()
{
	HierarchyNodePtr node;

	int kind;
	m_stream >> kind;

	switch (kind)
	{
		case NodeKind::Note:
		{
			node = std::make_unique<Note>();
			node->accept(*this);
		}
		break;

		case NodeKind::NotesFolder:
		{
			node = std::make_unique<NotesFolder>();
			node->accept(*this);
		}
		break;

		default:
			assert(0);
	}

	return node;
}

//-----------------------------------------------------------------------------
