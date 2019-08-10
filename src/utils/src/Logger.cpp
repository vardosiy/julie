#include "utils/Logger.hpp"

#include <iostream>
#include <fstream>

//-----------------------------------------------------------------------------

namespace utils {

//-----------------------------------------------------------------------------

Logger::Logger() noexcept = default;

//-----------------------------------------------------------------------------

Logger::~Logger() noexcept = default;

//-----------------------------------------------------------------------------

Logger & Logger::getInstance() noexcept
{
	static Logger s_logger;
	return s_logger;
}

//-----------------------------------------------------------------------------

void Logger::setFile(std::string_view _file) noexcept
{
	m_fileName = _file;
}

//-----------------------------------------------------------------------------

void Logger::write(const std::string & _message)
{
	std::cout << _message << std::endl;

	if (!m_fileName.empty())
	{
		std::ofstream file(m_fileName, std::ios::app);
		file << _message << std::endl;
	}
}

//-----------------------------------------------------------------------------

} // namespace utils

//-----------------------------------------------------------------------------
