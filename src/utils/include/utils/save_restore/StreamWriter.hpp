#pragma once

#include <ostream>
#include <type_traits>

//-----------------------------------------------------------------------------

namespace utils::sr {

//-----------------------------------------------------------------------------

class StreamWriter
{
public:
	explicit StreamWriter(std::ostream & _stream);

	template<typename T>
	std::enable_if_t<std::is_arithmetic_v<T>> write(T _value);

	template<typename T>
	std::enable_if_t<std::is_enum_v<T>> write(T _value);

	void write(std::string_view _value);

private:
	std::ostream & m_stream;
};

//-----------------------------------------------------------------------------

template<typename T>
std::enable_if_t<std::is_arithmetic_v<T>> StreamWriter::write(T _value)
{
	m_stream.write(reinterpret_cast<const char *>(&_value), sizeof(_value));
}

//-----------------------------------------------------------------------------

template<typename T>
std::enable_if_t<std::is_enum_v<T>> StreamWriter::write(T _value)
{
	write(static_cast<int>(_value));
}

//-----------------------------------------------------------------------------

} // namespace utils::sr

//-----------------------------------------------------------------------------
