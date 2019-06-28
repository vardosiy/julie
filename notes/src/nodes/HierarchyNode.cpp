#include "Pch.hpp"

#include "HierarchyNode.hpp"

//-----------------------------------------------------------------------------

NodeTag::Enum HierarchyNode::getTag() const noexcept
{
	return m_tag;
}

//-----------------------------------------------------------------------------

void HierarchyNode::setTag(NodeTag::Enum _tag) noexcept
{
	m_tag = _tag;
}

//-----------------------------------------------------------------------------
