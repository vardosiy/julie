#pragma once

#include "core/Id.hpp"

#include <boost/noncopyable.hpp>
#include <unordered_map>
#include <string_view>
#include <memory>

//-----------------------------------------------------------------------------

namespace data {

//-----------------------------------------------------------------------------

class DataEntity;

class Project : boost::noncopyable
{
public:
	using EntityPtr = std::unique_ptr<DataEntity>;

	Project();
	~Project();

	void addEntity(EntityPtr&& _entity) noexcept;
	void removeEntity(const DataEntity& _entity) noexcept;

	DataEntity* findEntity(std::string_view _name) noexcept;
	const DataEntity* findEntity(std::string_view _name) const noexcept;

private:
	using EntitiesMap = std::unordered_map<std::string_view, EntityPtr>;

	EntitiesMap m_entities;
};

//-----------------------------------------------------------------------------

} // namespace data

//-----------------------------------------------------------------------------
