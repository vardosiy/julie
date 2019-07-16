#include "Pch.hpp"

#include "core/visitors/save_restore/StreamDeserializationVisitor.hpp"

#include "core/nodes/HierarchyNode.hpp"
#include "core/nodes/Note.hpp"
#include "core/nodes/NotesFolder.hpp"

//-----------------------------------------------------------------------------

namespace visitors::save_restore {

//-----------------------------------------------------------------------------

StreamDeserializationVisitor::StreamDeserializationVisitor(std::istream & _stream) noexcept
	: StreamReader{ _stream }
{
}

//-----------------------------------------------------------------------------

nodes::HierarchyNodePtr StreamDeserializationVisitor::run()
{
	nodes::HierarchyNodePtr rootNode = deserializeNode();
	ASSERT(rootNode->getKind() == enums::NodeKind::NotesFolder, "Root element have to be a folder");

	return rootNode;
}

//-----------------------------------------------------------------------------

void StreamDeserializationVisitor::operator() (nodes::Note & _note)
{
	const std::string text{ readString() };

	_note.setText(text);
}

//-----------------------------------------------------------------------------

void StreamDeserializationVisitor::operator() (nodes::NotesFolder & _notesFolder)
{
	const std::string folderName{ readString() };
	const int childNodesCount{ readInt32() };

	_notesFolder.setName(folderName);

	for (int i{ 0 }; i < childNodesCount; ++i)
	{
		nodes::HierarchyNodePtr node = deserializeNode();
		_notesFolder.addChildNode(std::move(node));
	}
}

//-----------------------------------------------------------------------------

nodes::HierarchyNodePtr StreamDeserializationVisitor::deserializeNode()
{
	const int kind{ readInt32() };
	ASSERT(kind >= 0 && kind < enums::NodeKind::Count, "Invalid enumerator deserialized");
	const int tag{ readInt32() };
	ASSERT(tag >= 0 && tag < enums::NodeTag::Count, "Invalid enumerator deserialized");

	nodes::HierarchyNodePtr node;
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
		ASSERT_FALSE("Unhandled case");
	}

	node->setTag(static_cast<enums::NodeTag::Enum>(tag));

	return node;
}

//-----------------------------------------------------------------------------

} // namespace visitors::save_restore

//-----------------------------------------------------------------------------
