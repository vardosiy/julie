#pragma once

#include <boost/noncopyable.hpp>
#include <string>

//-----------------------------------------------------------------------------

namespace data {

//-----------------------------------------------------------------------------

class DataEntity : boost::noncopyable
{
public:
	DataEntity(std::string _name);
	virtual ~DataEntity();

	const std::string& getName() const noexcept;
	void setName(std::string _name) noexcept;

private:
	std::string m_name;
};

//-----------------------------------------------------------------------------

} // namespace data

//-----------------------------------------------------------------------------
