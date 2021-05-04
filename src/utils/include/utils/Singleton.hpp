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
	Singleton() = default;
	~Singleton() = default;
};

//-----------------------------------------------------------------------------

template<typename T>
inline T& Singleton<T>::getInstance() noexcept
{
	static T s_instance;
	return s_instance;
}

//-----------------------------------------------------------------------------
} // namespace utils
//-----------------------------------------------------------------------------
