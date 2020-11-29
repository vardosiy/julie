#pragma once

#include <string>

namespace jl {

class Entity
{
public:
	const std::string& getName() const noexcept		{ return m_name; }
	void setName(std::string _name) noexcept		{ m_name = std::move(_name); }

protected:
	Entity() = default;
	~Entity() = default;

private:
	std::string m_name;
};

} // namespace jl
