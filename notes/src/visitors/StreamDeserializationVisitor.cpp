#include "Pch.hpp"

#include "StreamDeserializationVisitor.hpp"

#include "nodes/HierarchyNode.hpp"
#include "nodes/Note.hpp"
#include "nodes/NotesFolder.hpp"

#include "nodes/NodesFactory.hpp"

//-----------------------------------------------------------------------------

StreamDeserializationVisitor::StreamDeserializationVisitor(std::istream & _stream) noexcept
	: m_stream{ _stream }
{
}

//-----------------------------------------------------------------------------

nodes::NotesFolderPtr StreamDeserializationVisitor::run()
{
	nodes::HierarchyNodePtr rootNode = deserializeNode();
	assert(rootNode->getKind() == enums::NodeKind::NotesFolder);

	return nodes::NotesFolderPtr(dynamic_cast<nodes::NotesFolder *>(rootNode.release()));
}

//-----------------------------------------------------------------------------

void StreamDeserializationVisitor::operator() (nodes::Note & _note)
{
	int tag;
	std::string text;

	m_stream
		>> tag
		>> text;

	_note.setTag(static_cast<enums::NodeTag::Enum>(tag));
	_note.setText(text);
}

//-----------------------------------------------------------------------------

void StreamDeserializationVisitor::operator() (nodes::NotesFolder & _notesFolder)
{
	std::string folderName;
	int tag;
	int childNodesCount;

	m_stream
		>> folderName
		>> tag
		>> childNodesCount;

	_notesFolder.setName(folderName);
	_notesFolder.setTag(static_cast<enums::NodeTag::Enum>(tag));

	for (int i{ 0 }; i < childNodesCount; ++i)
	{
		nodes::HierarchyNodePtr node = deserializeNode();
		_notesFolder.addChildNode(std::move(node));
	}
}

//-----------------------------------------------------------------------------

nodes::HierarchyNodePtr StreamDeserializationVisitor::deserializeNode()
{
	nodes::HierarchyNodePtr node;

	int kind;
	m_stream >> kind;

	switch (kind)
	{
		case enums::NodeKind::Note:
		{
			node = std::make_unique<nodes::Note>();
			node->accept(*this);
		}
		break;

		case enums::NodeKind::NotesFolder:
		{
			node = std::make_unique<nodes::NotesFolder>();
			node->accept(*this);
		}
		break;

		default:
			assert(0);
	}

	return node;
}

//-----------------------------------------------------------------------------
