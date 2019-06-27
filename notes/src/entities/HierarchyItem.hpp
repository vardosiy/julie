#ifndef __HIERARCHY_ITEM_HPP__
#define __HIERARCHY_ITEM_HPP__

//-----------------------------------------------------------------------------

#include <boost/noncopyable.hpp>

//-----------------------------------------------------------------------------

class HierarchyItem : boost::noncopyable
{
public:
	virtual ~HierarchyItem() noexcept = default;
};

//-----------------------------------------------------------------------------

#endif // __HIERARCHY_ITEM_HPP__
