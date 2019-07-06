#include "Pch.hpp"

#include "Logger.hpp"

//-----------------------------------------------------------------------------

Logger::Logger() noexcept = default;

//-----------------------------------------------------------------------------

Logger::~Logger() noexcept = default;

//-----------------------------------------------------------------------------

Logger * Logger::getInstance()
{
	static Logger s_loger;
	return &s_loger;
}

//-----------------------------------------------------------------------------

void Logger::setFile(std::string_view _file)
{
	m_fileName = _file;
}

//-----------------------------------------------------------------------------

void Logger::write(const boost::format & _message)
{
	std::cout << _message << std::endl;

	if (!m_fileName.empty())
	{
		std::ofstream file(m_fileName, std::ios::app);
		file << _message << std::endl;
	}
}

//-----------------------------------------------------------------------------
