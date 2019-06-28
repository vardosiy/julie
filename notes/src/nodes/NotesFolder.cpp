#include "Pch.hpp"

#include "NotesFolder.hpp"

#include "visitors/Visitor.hpp"

//-----------------------------------------------------------------------------

NotesFolder::NotesFolder(std::string_view _name) noexcept
	: m_name(_name)
{
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
	m_childNodes.emplace_back(std::forward<HierarchyNodePtr>(_node));
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

NodeKind::Enum NotesFolder::getKind() const noexcept
{
	return NodeKind::NotesFolder;
}

//-----------------------------------------------------------------------------

void NotesFolder::accept(Visitor & _visitor)
{
	_visitor.visit(*this);
}

//-----------------------------------------------------------------------------
