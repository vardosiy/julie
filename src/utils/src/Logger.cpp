#include "utils/Logger.hpp"

#include <iostream>

//-----------------------------------------------------------------------------

namespace utils {

//-----------------------------------------------------------------------------

Logger::Logger()
	: m_fileStream(k_logFile.data(), std::ios::app)
{
}

//-----------------------------------------------------------------------------

void Logger::write(const std::string & _message)
{
	writeConsole(_message);
	writeFile(_message);
}

//-----------------------------------------------------------------------------

void Logger::writeConsole(const std::string & _message)
{
	std::cout << _message << '\n';
}

//-----------------------------------------------------------------------------

void Logger::writeFile(const std::string & _message)
{
	if (m_fileStream.is_open())
	{
		m_fileStream << _message << '\n';
	}
}

//-----------------------------------------------------------------------------

} // namespace utils

//-----------------------------------------------------------------------------
