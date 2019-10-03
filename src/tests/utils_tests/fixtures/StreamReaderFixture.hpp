#include <gtest/gtest.h>

#include <sstream>

class StreamReaderFixture : public testing::Test
{
protected:
	template<typename T>
	void writeValue(const T _value)
	{
		m_stream.write(reinterpret_cast<const char *>(&_value), sizeof(_value));
	}

protected:
	std::stringstream m_stream;
};
