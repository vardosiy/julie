#ifndef __STREAM_WRITER_HPP__
#define __STREAM_WRITER_HPP__

//-----------------------------------------------------------------------------

#include <ostream>
#include <type_traits>

//-----------------------------------------------------------------------------

namespace utils::save_restore {

//-----------------------------------------------------------------------------

class StreamWriter
{
public:
	StreamWriter(std::ostream & _stream);

	void write(bool _val) { writeValue(_val); }
	void write(char _val) { writeValue(_val); }
	void write(double _val) { writeValue(_val); }
	void write(int16_t _val) { writeValue(_val); }
	void write(int32_t _val) { writeValue(_val); }
	void write(int64_t _val) { writeValue(_val); }

	void write(std::string_view _val);

private:
	template<typename T>
	typename std::enable_if_t<std::is_arithmetic_v<T>, void> writeValue(T _val);

private:
	std::ostream & m_stream;
};

//-----------------------------------------------------------------------------

template<typename T>
inline typename std::enable_if_t<std::is_arithmetic_v<T>, void> StreamWriter::writeValue(T _val)
{
	m_stream.write(reinterpret_cast<const char *>(&_val), sizeof(T));
}

//-----------------------------------------------------------------------------

} // namespace utils::save_restore

//-----------------------------------------------------------------------------

#endif // __STREAM_WRITER_HPP__
