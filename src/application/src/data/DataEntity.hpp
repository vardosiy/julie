#pragma once

#include "core/Id.hpp"

#include <boost/noncopyable.hpp>

class DataEntity : boost::noncopyable
{
public:
	DataEntity(Id _id);
	~DataEntity();

	const Id& getId() const noexcept;

private:
	Id m_id;
};
