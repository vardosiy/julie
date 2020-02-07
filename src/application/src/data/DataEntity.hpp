#pragma once

#include "core/Id.hpp"

#include <boost/noncopyable.hpp>

//-----------------------------------------------------------------------------

namespace data {

//-----------------------------------------------------------------------------

class DataEntity : boost::noncopyable
{
public:
	DataEntity(Id _id);
	~DataEntity();

	const Id& getName() const noexcept;

private:
	Id m_id;
};

//-----------------------------------------------------------------------------

} // namespace data

//-----------------------------------------------------------------------------
