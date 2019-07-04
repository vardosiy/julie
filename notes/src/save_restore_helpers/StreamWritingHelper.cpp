#include "Pch.hpp"

#include "StreamWritingHelper.hpp"

//-----------------------------------------------------------------------------

namespace save_restore {

//-----------------------------------------------------------------------------

StreamWritingHelper::StreamWritingHelper(std::ostream & _stream)
	: m_stream{ _stream }
{
}

//-----------------------------------------------------------------------------

void StreamWritingHelper::write(std::string_view _val)
{
	const int size{ static_cast<int>(_val.size()) };

	write(size);
	m_stream.write(_val.data(), size);
}

//-----------------------------------------------------------------------------

} // namespace save_restore

//-----------------------------------------------------------------------------
