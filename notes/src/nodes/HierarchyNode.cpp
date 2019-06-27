#include "Pch.hpp"

#include "HierarchyNode.hpp"

//-----------------------------------------------------------------------------

HierarchyNode::HierarchyNode()
	: m_tag(NodeTag::NonTaged)
{
}

//-----------------------------------------------------------------------------

NodeTag HierarchyNode::getTag() const
{
	return m_tag;
}

//-----------------------------------------------------------------------------

void HierarchyNode::setTag(NodeTag _tag)
{
	m_tag = _tag;
}

//-----------------------------------------------------------------------------
