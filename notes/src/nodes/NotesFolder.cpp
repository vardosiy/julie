#include "Pch.hpp"

#include "NotesFolder.hpp"

//-----------------------------------------------------------------------------

NotesFolder::NotesFolder(std::string_view _name)
	: m_name(_name)
{
}

//-----------------------------------------------------------------------------

std::string_view NotesFolder::getName() const
{
	return m_name;
}

//-----------------------------------------------------------------------------

void NotesFolder::setName(std::string_view _name)
{
	m_name = _name;
}

//-----------------------------------------------------------------------------

void NotesFolder::addNode(HierarchyNodePtr _node)
{
	m_childNodes.emplace_back(std::forward<HierarchyNodePtr>(_node));
}

//-----------------------------------------------------------------------------

int NotesFolder::getNodesCount() const
{
	return static_cast<int>(m_childNodes.size());
}

//-----------------------------------------------------------------------------

const HierarchyNode & NotesFolder::getNode(int _idx)
{
	return *m_childNodes.at(_idx);
}

//-----------------------------------------------------------------------------
