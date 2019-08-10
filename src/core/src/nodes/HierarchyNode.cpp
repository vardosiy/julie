#include "core/nodes/HierarchyNode.hpp"

//-----------------------------------------------------------------------------

namespace nodes {

//-----------------------------------------------------------------------------

HierarchyNode::~HierarchyNode() noexcept = default;

//-----------------------------------------------------------------------------

HierarchyNode::HierarchyNode(enums::NodeKind::Enum _kind) noexcept
	: m_kind{ _kind }
	, m_tag{ enums::NodeTag::NonTagged }
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
