#include "StreamReaderFixture.hpp"

#include "utils/save_restore/StreamReader.hpp"

#include <functional>

//------------------------------------------------------------------------------

template<typename T>
using ReadMethod = T(utils::sr::StreamReader::*)();

template<typename T>
void testSingleRead(const T _value, ReadMethod<T> _readMethod)
{
	std::stringstream stream;
	utils::sr::StreamReader reader(stream);

	stream.write(reinterpret_cast<const char *>(&_value), sizeof(_value));
	const T readed{ (reader.*_readMethod)() };

	EXPECT_EQ(stream.gcount(), sizeof(_value));
	EXPECT_EQ(_value, readed);
}

//------------------------------------------------------------------------------

TEST_F(StreamReaderFixture, ReadSingleBool)
{
	testSingleRead<bool>(true, &utils::sr::StreamReader::readBool);
}

//------------------------------------------------------------------------------

TEST_F(StreamReaderFixture, ReadSingleChar)
{
	testSingleRead<char>('c', &utils::sr::StreamReader::readChar);
}

//------------------------------------------------------------------------------

TEST_F(StreamReaderFixture, ReadSingleDouble)
{
	testSingleRead<double>(5.63, &utils::sr::StreamReader::readDouble);
}

//------------------------------------------------------------------------------

TEST_F(StreamReaderFixture, ReadSingleNegativeDouble)
{
	testSingleRead<double>(-5.63, &utils::sr::StreamReader::readDouble);
}

//------------------------------------------------------------------------------

TEST_F(StreamReaderFixture, ReadSingleInt16)
{
	testSingleRead<short>(12681, &utils::sr::StreamReader::readInt16);
}

//------------------------------------------------------------------------------

TEST_F(StreamReaderFixture, ReadSingleNegativeInt16)
{
	testSingleRead<short>(-12681, &utils::sr::StreamReader::readInt16);
}

//------------------------------------------------------------------------------

TEST_F(StreamReaderFixture, ReadSingleInt32)
{
	testSingleRead<int>(166230, &utils::sr::StreamReader::readInt32);
}

//------------------------------------------------------------------------------

TEST_F(StreamReaderFixture, ReadSingleNegativeInt32)
{
	testSingleRead<int>(-166230, &utils::sr::StreamReader::readInt32);
}

//------------------------------------------------------------------------------

TEST_F(StreamReaderFixture, ReadSingleInt64)
{
	testSingleRead<long long>(34596785, &utils::sr::StreamReader::readInt64);
}

//------------------------------------------------------------------------------

TEST_F(StreamReaderFixture, ReadSingleNegativeInt64)
{
	testSingleRead<long long>(-34596785, &utils::sr::StreamReader::readInt64);
}

//------------------------------------------------------------------------------
