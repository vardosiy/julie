#ifndef __STREAM_WRITING_HELPER_HPP__
#define __STREAM_WRITING_HELPER_HPP__

//-----------------------------------------------------------------------------

#include <ostream>
#include <type_traits>

//-----------------------------------------------------------------------------

namespace save_restore {

//-----------------------------------------------------------------------------

class StreamWritingHelper
{
public:
	StreamWritingHelper(std::ostream & _stream);

	void write(bool _val) { writeInternal(_val); }
	void write(char _val) { writeInternal(_val); }
	void write(int16_t _val) { writeInternal(_val); }
	void write(int32_t _val) { writeInternal(_val); }
	void write(int64_t _val) { writeInternal(_val); }
	void write(double _val) { writeInternal(_val); }

	void write(std::string_view _val);

private:
	template<typename T>
	typename std::enable_if_t<std::is_arithmetic_v<T>, void> writeInternal(T _val);

private:
	std::ostream & m_stream;
};

//-----------------------------------------------------------------------------

template<typename T>
typename std::enable_if_t<std::is_arithmetic_v<T>, void> StreamWritingHelper::writeInternal(T _val)
{
	m_stream.write(reinterpret_cast<const char *>(&_val), sizeof(T));
}

//-----------------------------------------------------------------------------

} // namespace save_restore

//-----------------------------------------------------------------------------

#endif // __STREAM_WRITING_HELPER_HPP__
