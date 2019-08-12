#include "core/nodes/HierarchyNode.hpp"

//-----------------------------------------------------------------------------

namespace nodes {

//-----------------------------------------------------------------------------

HierarchyNode::~HierarchyNode() noexcept = default;

//-----------------------------------------------------------------------------

HierarchyNode::HierarchyNode(enums::NodeKind _kind) noexcept
	: m_kind(_kind)
	, m_tag(enums::NodeTag::NonTagged)
{
}

//-----------------------------------------------------------------------------

enums::NodeKind HierarchyNode::getKind() const noexcept
{
	return m_kind;
}

//-----------------------------------------------------------------------------

enums::NodeTag HierarchyNode::getTag() const noexcept
{
	return m_tag;
}

//-----------------------------------------------------------------------------

void HierarchyNode::setTag(enums::NodeTag _tag) noexcept
{
	m_tag = _tag;
}

//-----------------------------------------------------------------------------

} // namespace nodes

//-----------------------------------------------------------------------------
