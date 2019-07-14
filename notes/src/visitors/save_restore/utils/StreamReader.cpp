#include "Pch.hpp"

#include "StreamReader.hpp"

//-----------------------------------------------------------------------------

namespace utils::save_restore {

//-----------------------------------------------------------------------------

StreamReader::StreamReader(std::istream & _stream)
	: m_stream{ _stream }
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

} // namespace utils::save_restore

//-----------------------------------------------------------------------------
