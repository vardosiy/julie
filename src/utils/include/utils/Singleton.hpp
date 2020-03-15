#pragma once

//-----------------------------------------------------------------------------

namespace utils {

//-----------------------------------------------------------------------------

template<typename T>
class Singleton
{
public:
	static T& getInstance() noexcept;

protected:
	Singleton() noexcept = default;
	~Singleton() noexcept = default;
};

//-----------------------------------------------------------------------------

template<typename T>
T& Singleton<T>::getInstance() noexcept
{
	static T s_instance;
	return s_instance;
}

//-----------------------------------------------------------------------------

} // namespace utils

//-----------------------------------------------------------------------------
