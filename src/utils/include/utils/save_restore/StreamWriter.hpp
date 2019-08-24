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

	void write(bool _val) { writeValue(_val); }
	void write(char _val) { writeValue(_val); }
	void write(double _val) { writeValue(_val); }
	void write(int16_t _val) { writeValue(_val); }
	void write(int32_t _val) { writeValue(_val); }
	void write(int64_t _val) { writeValue(_val); }

	void write(std::string_view _val);

	template<typename T>
	std::enable_if_t<std::is_enum_v<T>> write(T _val);

private:
	template<typename T>
	std::enable_if_t<std::is_arithmetic_v<T>> writeValue(T _val);

private:
	std::ostream & m_stream;
};

//-----------------------------------------------------------------------------

template<typename T>
std::enable_if_t<std::is_enum_v<T>> StreamWriter::write(T _val)
{
	write(static_cast<int>(_val));
}

//-----------------------------------------------------------------------------

template<typename T>
std::enable_if_t<std::is_arithmetic_v<T>> StreamWriter::writeValue(T _val)
{
	m_stream.write(reinterpret_cast<const char *>(&_val), sizeof(T));
}

//-----------------------------------------------------------------------------

} // namespace utils::sr

//-----------------------------------------------------------------------------
