#pragma once

#include <type_traits>

//-----------------------------------------------------------------------------

namespace utils {

//-----------------------------------------------------------------------------

template<typename T, size_t Size, size_t Align>
class FastPimpl
{
public:
	template<typename ... Args>
	constexpr FastPimpl(Args&&... _args);
	~FastPimpl();

	constexpr T* get() noexcept;
	constexpr const T* get() const noexcept;

	constexpr T* operator-> () noexcept					{ return get(); }
	constexpr const T* operator-> () const noexcept		{ return get(); }

	constexpr T& operator* ()							{ return *get(); }
	constexpr const T& operator* () const				{ return *get(); }

private:
	std::aligned_storage_t<Size, Align> m_value;
};

//-----------------------------------------------------------------------------

template<typename T, size_t Size, size_t Align>
template<typename ... Args>
inline constexpr FastPimpl<T, Size, Align>::FastPimpl(Args&&... _args)
{
	new(&m_value) T(std::forward<Args>(_args)...);
}

template<typename T, size_t Size, size_t Align>
inline FastPimpl<T, Size, Align>::~FastPimpl()
{
	static_assert(Size  == sizeof(T),  "Actual size of type used in FastPimpl does not match the specified one");
	static_assert(Align == alignof(T), "Actual alignment of type used in FastPimpl does not match the specified one");

	get()->~T();
}

template<typename T, size_t Size, size_t Align>
inline constexpr T* FastPimpl<T, Size, Align>::get() noexcept
{
	return reinterpret_cast<T*>(&m_value);
}

template<typename T, size_t Size, size_t Align>
inline constexpr const T* FastPimpl<T, Size, Align>::get() const noexcept
{
	return reinterpret_cast<const T*>(&m_value);
}

//-----------------------------------------------------------------------------


} // namespace utils

//-----------------------------------------------------------------------------
