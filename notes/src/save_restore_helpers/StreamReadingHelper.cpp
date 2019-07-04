#include "Pch.hpp"

#include "StreamReadingHelper.hpp"

//-----------------------------------------------------------------------------

namespace save_restore {

//-----------------------------------------------------------------------------

StreamReadingHelper::StreamReadingHelper(std::istream & _stream)
	: m_stream{ _stream }
{
}

//-----------------------------------------------------------------------------

std::string StreamReadingHelper::readString()
{
	const int size{ readInt32() };

	char buffer[256];
	m_stream.read(buffer, size);

	std::string result(buffer, size);
	return result;
}

//-----------------------------------------------------------------------------

} // namespace save_restore

//-----------------------------------------------------------------------------
