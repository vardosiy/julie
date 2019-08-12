#include "utils/save_restore/StreamReader.hpp"

#include <vector>

//-----------------------------------------------------------------------------

namespace utils::sr {

//-----------------------------------------------------------------------------

StreamReader::StreamReader(std::istream & _stream)
	: m_stream(_stream)
{
}

//-----------------------------------------------------------------------------

std::string StreamReader::readString()
{
	const int size{ readInt32() };

	// TODO: check if char[] is better
	std::vector<char> buffer(size);
	m_stream.read(buffer.data(), size);

	std::string result(buffer.data(), size);
	return result;
}

//-----------------------------------------------------------------------------

} // namespace utils::sr

//-----------------------------------------------------------------------------
