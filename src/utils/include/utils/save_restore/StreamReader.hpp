#pragma once

#include "utils/Assert.hpp"
#include "utils/EnumUtils.hpp"

#include <array>
#include <istream>
#include <type_traits>

//-----------------------------------------------------------------------------

namespace utils::sr {

//-----------------------------------------------------------------------------

class StreamReader
{
public:
	explicit StreamReader(std::istream & _stream);

	bool readBool() { return readValue<bool>(); }
	char readChar() { return readValue<char>(); }
	double readDouble() { return readValue<double>(); }
	int16_t readInt16() { return readValue<int16_t>(); }
	int32_t readInt32() { return readValue<int32_t>(); }
	int64_t readInt64() { return readValue<int64_t>(); }

	std::string readString();

	template<typename T>
	std::enable_if_t<std::is_enum_v<T>, T> readEnum();

private:
	template<typename T>
	std::enable_if_t<std::is_arithmetic_v<T>, T> readValue();

private:
	std::istream & m_stream;
};

//-----------------------------------------------------------------------------

template<typename T>
std::enable_if_t<std::is_enum_v<T>, T> StreamReader::readEnum()
{
	const T value{ static_cast<T>(readInt32()) };
	ASSERT(enums::isValid(value), "Invalid enumerator restored");

	return value;
}

//-----------------------------------------------------------------------------

template<typename T>
std::enable_if_t<std::is_arithmetic_v<T>, T> StreamReader::readValue()
{
	T value;
	m_stream.read(reinterpret_cast<char*>(&value), sizeof(T));

	return value;
}

//-----------------------------------------------------------------------------

} // namespace utils::sr

//-----------------------------------------------------------------------------
