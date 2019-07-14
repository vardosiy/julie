#ifndef __HIERARCHY_NODE_HPP__
#define __HIERARCHY_NODE_HPP__

//-----------------------------------------------------------------------------

#include "enums/NodeTag.hpp"
#include "enums/NodeKind.hpp"

//-----------------------------------------------------------------------------

namespace visitors {

class Visitor;

}

//-----------------------------------------------------------------------------

namespace nodes {

//-----------------------------------------------------------------------------

class HierarchyNode : boost::noncopyable
{
public:
	virtual ~HierarchyNode() noexcept;

	enums::NodeKind::Enum getKind() const noexcept;
	enums::NodeTag::Enum getTag() const noexcept;

	void setTag(enums::NodeTag::Enum _tag) noexcept;

	virtual void accept(visitors::Visitor & _visitor) = 0;

protected:
	HierarchyNode(enums::NodeKind::Enum _kind) noexcept;

private:
	enums::NodeKind::Enum m_kind;
	enums::NodeTag::Enum m_tag;
};

//-----------------------------------------------------------------------------

} // namespace nodes

//-----------------------------------------------------------------------------

#endif // __HIERARCHY_NODE_HPP__
