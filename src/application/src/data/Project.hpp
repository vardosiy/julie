#pragma once

#include "core/Id.hpp"

#include <boost/noncopyable.hpp>
#include <vector>
#include <memory>

//-----------------------------------------------------------------------------

namespace data {

//-----------------------------------------------------------------------------

class DataEntity;

class Project : boost::noncopyable
{
public:
	Project(std::string_view _fileName);
	~Project();

	DataEntity* findEntity(Id _id) noexcept;
	const DataEntity* findEntity(Id _id) const noexcept;

	void removeEntity(Id _id) noexcept;

private:
	std::vector<std::unique_ptr<DataEntity>> m_entities;
};

//-----------------------------------------------------------------------------

} // namespace data

//-----------------------------------------------------------------------------
