#pragma once

namespace utils {

struct Noncopyable
{
protected:
	constexpr Noncopyable() = default;

	Noncopyable(const Noncopyable&) = delete;
	Noncopyable& operator=(const Noncopyable&) = delete;

	constexpr Noncopyable(Noncopyable&&) = default;
	constexpr Noncopyable& operator=(Noncopyable&&) = default;
};

} // namespace utils
