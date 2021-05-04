#include "utils/save_restore/StreamWriter.hpp"

//-----------------------------------------------------------------------------
namespace utils::sr {
//-----------------------------------------------------------------------------

StreamWriter::StreamWriter(std::ostream& _stream)
	: m_stream(_stream)
{
}

//-----------------------------------------------------------------------------

void StreamWriter::write(std::string_view _val)
{
	const int size{ static_cast<int>(_val.size()) };

	write(size);
	m_stream.write(_val.data(), size);
}

//-----------------------------------------------------------------------------
} // namespace utils::sr
//-----------------------------------------------------------------------------
