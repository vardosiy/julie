#pragma once

#include "utils/Assert.hpp"
#include "utils/EnumUtils.hpp"

#include <istream>
#include <type_traits>

//-----------------------------------------------------------------------------

namespace utils::sr {

//-----------------------------------------------------------------------------

class StreamReader
{
public:
	explicit StreamReader(std::istream & _stream);

	template<typename T>
	std::enable_if_t<std::is_arithmetic_v<T>, T> read();

	template<typename T>
	std::enable_if_t<std::is_enum_v<T>, T> read();

	template<typename T>
	std::enable_if_t<std::is_same_v<T, std::string>, T> read();

private:
	std::istream & m_stream;
};

//-----------------------------------------------------------------------------

template<typename T>
std::enable_if_t<std::is_arithmetic_v<T>, T> StreamReader::read()
{
	T value;
	m_stream.read(reinterpret_cast<char *>(&value), sizeof(T));

	return value;
}

//-----------------------------------------------------------------------------

template<typename T>
std::enable_if_t<std::is_enum_v<T>, T> StreamReader::read()
{
	const T value{ static_cast<T>(read<int>()) };
	ASSERT(enums::isValid(value), "Invalid enumerator restored");

	return value;
}

//-----------------------------------------------------------------------------

template<typename T>
std::enable_if_t<std::is_same_v<T, std::string>, T> StreamReader::read()
{
	const int size{ read<int>() };

	std::vector<char> buffer(size);
	m_stream.read(buffer.data(), size);

	return std::string(buffer.data(), size);
}

//-----------------------------------------------------------------------------

} // namespace utils::sr

//-----------------------------------------------------------------------------
