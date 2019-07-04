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
	assert(_node);
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
		assert(item);
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
