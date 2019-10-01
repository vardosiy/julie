#include <gtest/gtest.h>

#include "utils/save_restore/StreamReader.hpp"

#include <sstream>
#include <functional>

//------------------------------------------------------------------------------

template<typename T>
using ReadMethod = T(utils::sr::StreamReader::*)();

template<typename T>
void testRead(const T _value, ReadMethod<T> _readMethod)
{
	std::stringstream stream;
	utils::sr::StreamReader reader(stream);

	stream.write(reinterpret_cast<const char *>(&_value), sizeof(_value));
	const T readed{ (reader.*_readMethod)() };

	EXPECT_EQ(_value, readed);
}

//------------------------------------------------------------------------------

TEST(StreamReader, ReadSingleValuePositive)
{
	testRead<bool>(true, &utils::sr::StreamReader::readBool);
	testRead<char>('c', &utils::sr::StreamReader::readChar);
	testRead<double>(5.63, &utils::sr::StreamReader::readDouble);
	testRead<short>(12681, &utils::sr::StreamReader::readInt16);
	testRead<int>(166230, &utils::sr::StreamReader::readInt32);
	testRead<long long>(161460, &utils::sr::StreamReader::readInt64);
}

//------------------------------------------------------------------------------

TEST(StreamReader, ReadSingleValueNegative)
{
	testRead<bool>(false, &utils::sr::StreamReader::readBool);
	testRead<char>(-('c'), &utils::sr::StreamReader::readChar);
	testRead<double>(-5.63, &utils::sr::StreamReader::readDouble);
	testRead<short>(-12681, &utils::sr::StreamReader::readInt16);
	testRead<int>(-166230, &utils::sr::StreamReader::readInt32);
	testRead<long long>(-161460, &utils::sr::StreamReader::readInt64);
}

//------------------------------------------------------------------------------
