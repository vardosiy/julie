#ifndef __HIERARCHY_NODE_HPP__
#define __HIERARCHY_NODE_HPP__

//-----------------------------------------------------------------------------

#include "enums/NodeTag.hpp"
#include "enums/NodeKind.hpp"

//-----------------------------------------------------------------------------

class Visitor;

//-----------------------------------------------------------------------------

class HierarchyNode : boost::noncopyable
{
public:
	virtual ~HierarchyNode() = default;

	NodeTag::Enum getTag() const noexcept;
	void setTag(NodeTag::Enum _tag) noexcept;

	virtual NodeKind::Enum getKind() const noexcept = 0;

	virtual void accept(Visitor & _visitor) = 0;

private:
	NodeTag::Enum m_tag{ NodeTag::NonTaged };
};

//-----------------------------------------------------------------------------

#endif // __HIERARCHY_NODE_HPP__
