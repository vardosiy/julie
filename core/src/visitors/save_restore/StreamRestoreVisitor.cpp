#include "Pch.hpp"

#include "core/visitors/save_restore/StreamRestoreVisitor.hpp"

#include "core/nodes/Note.hpp"
#include "core/nodes/NotesFolder.hpp"

//-----------------------------------------------------------------------------

namespace visitors::save_restore {

//-----------------------------------------------------------------------------

StreamRestoreVisitor::StreamRestoreVisitor(std::istream & _stream) noexcept
	: StreamReader{ _stream }
{
}

//-----------------------------------------------------------------------------

void StreamRestoreVisitor::operator() (nodes::Note & _note)
{
	restoreCommon(_note);

	const std::string text{ readString() };
	_note.setText(text);
}

//-----------------------------------------------------------------------------

void StreamRestoreVisitor::operator() (nodes::NotesFolder & _notesFolder)
{
	restoreCommon(_notesFolder);

	const std::string folderName{ readString() };
	_notesFolder.setName(folderName);

	const int childNodesCount{ readInt32() };
	for (int i{ 0 }; i < childNodesCount; ++i)
	{
		nodes::HierarchyNodePtr node = deserializeNode();
		_notesFolder.addChild(std::move(node));
	}
}

//-----------------------------------------------------------------------------

void StreamRestoreVisitor::restoreCommon(nodes::HierarchyNode & _hierarchyNode)
{
	const int tag{ readInt32() };
	//ASSERT(enums::NodeTag::isValid(tag), "Invalid enumerator deserialized");

	_hierarchyNode.setTag(static_cast<enums::NodeTag::Enum>(tag));
}

//-----------------------------------------------------------------------------

nodes::HierarchyNodePtr StreamRestoreVisitor::deserializeNode()
{
	const int kind{ readInt32() };
	//ASSERT(enums::NodeKind::isValid(kind), "Invalid enumerator deserialized");

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

	return node;
}

//-----------------------------------------------------------------------------

} // namespace visitors::save_restore

//-----------------------------------------------------------------------------
