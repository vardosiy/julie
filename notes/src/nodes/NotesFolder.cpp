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

int NotesFolder::getChildNodesCount() const noexcept
{
	return static_cast<int>(m_childNodes.size());
}

//-----------------------------------------------------------------------------

void NotesFolder::forEachChildNode(std::function<void(HierarchyNode &)> _callback)
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
