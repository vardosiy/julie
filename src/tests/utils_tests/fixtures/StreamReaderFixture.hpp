#include <gtest/gtest.h>

#include <sstream>

class StreamReaderFixture : public testing::Test
{
protected:
	std::stringstream m_stream;
};
