#pragma once

#include <string_view>
#include <boost/format.hpp>

//-----------------------------------------------------------------------------

namespace utils {

//-----------------------------------------------------------------------------

class Logger
{
public:
	static Logger & getInstance() noexcept;

	template<typename ... Args>
	void log(std::string_view _message, Args && ... _args);

	void setFile(std::string_view _file) noexcept;

private:
	Logger() noexcept;
	~Logger() noexcept;

	void write(const boost::format & _message);

private:
	std::string m_fileName;
};

//-----------------------------------------------------------------------------

template<typename ... Args>
inline void Logger::log(std::string_view _message, Args && ... _args)
{
	boost::format message(_message.data());
	(message % ... % _args);

	write(message);
}

//-----------------------------------------------------------------------------

} // namespace utils

//-----------------------------------------------------------------------------
