#include "utils/save_restore/StreamReader.hpp"

#include <vector>

//-----------------------------------------------------------------------------

namespace utils::sr {

//-----------------------------------------------------------------------------

StreamReader::StreamReader(std::istream & _stream)
	: m_stream{ _stream }
{
}

//-----------------------------------------------------------------------------

std::string StreamReader::readString()
{
	const int size{ readInt32() };

	std::vector<char> buffer(size);
	m_stream.read(buffer.data(), size);

	return std::string(buffer.data(), size);
}

//-----------------------------------------------------------------------------

} // namespace utils::sr

//-----------------------------------------------------------------------------
