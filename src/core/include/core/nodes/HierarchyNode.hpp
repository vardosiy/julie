#pragma once

#include "core/enums/NodeTag.hpp"
#include "core/enums/NodeKind.hpp"

//#include <boost/noncopyable.hpp>

//-----------------------------------------------------------------------------

namespace visitors {
class Visitor;
}

//-----------------------------------------------------------------------------

namespace nodes {

//-----------------------------------------------------------------------------

class HierarchyNode// : boost::noncopyable
{
public:
	virtual ~HierarchyNode() noexcept;

	enums::NodeKind getKind() const noexcept;
	enums::NodeTag getTag() const noexcept;

	void setTag(enums::NodeTag _tag) noexcept;

	virtual void accept(visitors::Visitor & _visitor) = 0;

protected:
	HierarchyNode(enums::NodeKind _kind) noexcept;

private:
	enums::NodeKind m_kind;
	enums::NodeTag m_tag;
};

//-----------------------------------------------------------------------------

} // namespace nodes

//-----------------------------------------------------------------------------
