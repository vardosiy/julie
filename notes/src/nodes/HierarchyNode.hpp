#ifndef __HIERARCHY_NODE_HPP__
#define __HIERARCHY_NODE_HPP__

//-----------------------------------------------------------------------------

#include "enums/NodeTag.hpp"
#include "enums/NodeKind.hpp"

//-----------------------------------------------------------------------------

class Visitor;

//-----------------------------------------------------------------------------

namespace nodes {

//-----------------------------------------------------------------------------

class HierarchyNode : boost::noncopyable
{
public:
	virtual ~HierarchyNode() = default;

	enums::NodeTag::Enum getTag() const noexcept;
	void setTag(enums::NodeTag::Enum _tag) noexcept;

	virtual enums::NodeKind::Enum getKind() const noexcept = 0;

	virtual void accept(Visitor & _visitor) = 0;

private:
	enums::NodeTag::Enum m_tag{ enums::NodeTag::NonTaged };
};

//-----------------------------------------------------------------------------

} // namespace nodes

//-----------------------------------------------------------------------------

#endif // __HIERARCHY_NODE_HPP__
