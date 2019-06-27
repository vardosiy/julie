#ifndef __HIERARCHY_NODE_HPP__
#define __HIERARCHY_NODE_HPP__

//-----------------------------------------------------------------------------

#include "enums/NodeTag.hpp"

#include <boost/noncopyable.hpp>

//-----------------------------------------------------------------------------

class HierarchyNode : boost::noncopyable
{
public:
	HierarchyNode() noexcept;
	virtual ~HierarchyNode() = default;

	NodeTag getTag() const noexcept;
	void setTag(NodeTag _tag) noexcept;

private:
	NodeTag m_tag;
};

//-----------------------------------------------------------------------------

#endif // __HIERARCHY_NODE_HPP__
