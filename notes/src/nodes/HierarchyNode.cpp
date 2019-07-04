#include "Pch.hpp"

#include "HierarchyNode.hpp"

//-----------------------------------------------------------------------------

namespace nodes {

//-----------------------------------------------------------------------------

HierarchyNode::HierarchyNode(enums::NodeKind::Enum _kind) noexcept
	: m_kind{ _kind }
	, m_tag{ enums::NodeTag::NonTaged }
{
}

//-----------------------------------------------------------------------------

enums::NodeKind::Enum HierarchyNode::getKind() const noexcept
{
	return m_kind;
}

//-----------------------------------------------------------------------------

enums::NodeTag::Enum HierarchyNode::getTag() const noexcept
{
	return m_tag;
}

//-----------------------------------------------------------------------------

void HierarchyNode::setTag(enums::NodeTag::Enum _tag) noexcept
{
	m_tag = _tag;
}

//-----------------------------------------------------------------------------

} // namespace nodes

//-----------------------------------------------------------------------------
