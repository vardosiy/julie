#include "utils/Logger.hpp"

#include <iostream>
#include <fstream>

//-----------------------------------------------------------------------------

namespace utils {

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
