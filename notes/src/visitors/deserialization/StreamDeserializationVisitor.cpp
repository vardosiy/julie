#include "Pch.hpp"

#include "StreamDeserializationVisitor.hpp"

#include "nodes/HierarchyNode.hpp"
#include "nodes/Note.hpp"
#include "nodes/NotesFolder.hpp"

//-----------------------------------------------------------------------------

namespace visitors {

//-----------------------------------------------------------------------------

StreamDeserializationVisitor::StreamDeserializationVisitor(std::istream & _stream) noexcept
	: StreamReadingHelper(_stream)
{
}

//-----------------------------------------------------------------------------

nodes::HierarchyNodePtr StreamDeserializationVisitor::run()
{
	nodes::HierarchyNodePtr rootNode = deserializeNode();
	assert(rootNode->getKind() == enums::NodeKind::NotesFolder);

	return rootNode;
}

//-----------------------------------------------------------------------------

void StreamDeserializationVisitor::operator() (nodes::Note & _note)
{
	const int tag{ readInt32() };
	const std::string text{ readString() };

	_note.setTag(static_cast<enums::NodeTag::Enum>(tag));
	_note.setText(text);
}

//-----------------------------------------------------------------------------

void StreamDeserializationVisitor::operator() (nodes::NotesFolder & _notesFolder)
{
	const int tag{ readInt32() };
	const std::string folderName{ readString() };
	const int childNodesCount{ readInt32() };

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

	const int kind{ readInt32() };
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

} // namespace visitors

//-----------------------------------------------------------------------------
