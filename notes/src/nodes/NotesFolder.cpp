#include "Pch.hpp"

#include "NotesFolder.hpp"

#include "visitors/Visitor.hpp"

//-----------------------------------------------------------------------------

namespace nodes {

//-----------------------------------------------------------------------------

NotesFolder::NotesFolder() noexcept
	: HierarchyNode{ enums::NodeKind::NotesFolder }
{
}

//-----------------------------------------------------------------------------

NotesFolder::NotesFolder(std::string_view _name) noexcept
	: NotesFolder()
{
	m_name = _name;
}

//-----------------------------------------------------------------------------

std::string_view NotesFolder::getName() const noexcept
{
	return m_name;
}

//-----------------------------------------------------------------------------

void NotesFolder::setName(std::string_view _name) noexcept
{
	m_name = _name;
}

//-----------------------------------------------------------------------------

void NotesFolder::addChildNode(HierarchyNodePtr _node) noexcept
{
	ASSERT(_node, "Trying to add NULL node to childs");
	m_childNodes.emplace_back(std::move(_node));
}

//-----------------------------------------------------------------------------

void NotesFolder::removeChildNode(const HierarchyNode & _node) noexcept
{
	auto it = std::find_if(
		m_childNodes.cbegin(),
		m_childNodes.cend(),
		[&_node](const HierarchyNodePtr & _currentNode) -> bool
		{
			return _currentNode.get() == &_node;
		}
	);

	if (it != m_childNodes.cend())
	{
		m_childNodes.erase(it);
	}
	else
	{
		LOG("Trying to remove node, which is not a child of the folder");
	}
}

//-----------------------------------------------------------------------------

int NotesFolder::getChildNodesCount() const noexcept
{
	return static_cast<int>(m_childNodes.size());
}

//-----------------------------------------------------------------------------

void NotesFolder::forEachChildNode(NotesFolder::NodeCallback _callback)
{
	for (auto & item : m_childNodes)
	{
		ASSERT(item, "NULL child");
		_callback(*item);
	}
}

//-----------------------------------------------------------------------------

void NotesFolder::accept(visitors::Visitor & _visitor)
{
	_visitor(*this);
}

//-----------------------------------------------------------------------------

} // namespace nodes

//-----------------------------------------------------------------------------
