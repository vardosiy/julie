#pragma once

#include <istream>
#include <type_traits>

//-----------------------------------------------------------------------------

namespace utils::save_restore {

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

private:
	template<typename T>
	T readValue(std::enable_if_t<std::is_arithmetic_v<T>, void *> = nullptr);

private:
	std::istream & m_stream;
};

//-----------------------------------------------------------------------------

template<typename T>
inline T StreamReader::readValue(std::enable_if_t<std::is_arithmetic_v<T>, void *>)
{
	std::array<char, sizeof(T)> buffer;
	m_stream.read(buffer, sizeof(T));

	T * result{ reinterpret_cast<T *>(buffer) };
	return *result;
}

//-----------------------------------------------------------------------------

} // namespace utils::save_restore

//-----------------------------------------------------------------------------
