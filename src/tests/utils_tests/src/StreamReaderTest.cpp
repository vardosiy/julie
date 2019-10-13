#include "StreamReaderFixture.hpp"

#include "utils/save_restore/StreamReader.hpp"

#include <functional>

//------------------------------------------------------------------------------

template<typename T>
void testSingleRead(const T _value)
{
	std::stringstream stream;
	stream.write(reinterpret_cast<const char *>(&_value), sizeof(_value));

	utils::sr::StreamReader reader(stream);
	const T readed{ reader.read<T>() };

	EXPECT_EQ(stream.gcount(), sizeof(_value));
	EXPECT_EQ(_value, readed);
}

//------------------------------------------------------------------------------

TEST_F(StreamReaderFixture, ReadSingleBool)
{
	testSingleRead<bool>(true);
}

//------------------------------------------------------------------------------

TEST_F(StreamReaderFixture, ReadSingleChar)
{
	testSingleRead<char>('c');
}

//------------------------------------------------------------------------------

TEST_F(StreamReaderFixture, ReadSingleDouble)
{
	testSingleRead<double>(5.63);
}

//------------------------------------------------------------------------------

TEST_F(StreamReaderFixture, ReadSingleNegativeDouble)
{
	testSingleRead<double>(-5.63);
}

//------------------------------------------------------------------------------

TEST_F(StreamReaderFixture, ReadSingleInt16)
{
	testSingleRead<short>(12681);
}

//------------------------------------------------------------------------------

TEST_F(StreamReaderFixture, ReadSingleNegativeInt16)
{
	testSingleRead<short>(-12681);
}

//------------------------------------------------------------------------------

TEST_F(StreamReaderFixture, ReadSingleInt32)
{
	testSingleRead<int>(166230);
}

//------------------------------------------------------------------------------

TEST_F(StreamReaderFixture, ReadSingleNegativeInt32)
{
	testSingleRead<int>(-166230);
}

//------------------------------------------------------------------------------

TEST_F(StreamReaderFixture, ReadSingleInt64)
{
	testSingleRead<long long>(34596785);
}

//------------------------------------------------------------------------------

TEST_F(StreamReaderFixture, ReadSingleNegativeInt64)
{
	testSingleRead<long long>(-34596785);
}

//------------------------------------------------------------------------------

TEST_F(StreamReaderFixture, ReadString)
{
	const std::string str = "This string is test";
	const int size{ static_cast<int>(str.size()) };

	m_stream.write(reinterpret_cast<const char *>(&size), sizeof(size));
	m_stream.write(str.c_str(), str.size());

	utils::sr::StreamReader reader(m_stream);
	const std::string readed = reader.read<std::string>();

	EXPECT_EQ(str, readed);
}

//------------------------------------------------------------------------------
