#pragma once

#include <fmt/format.h>

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
	Logger() noexcept = default;
	~Logger() noexcept = default;

	void write(const std::string & _message);

private:
	std::string m_fileName;
};

//-----------------------------------------------------------------------------

template<typename ... Args>
void Logger::log(std::string_view _message, Args && ... _args)
{
	write(fmt::format(_message.data(), std::forward<Args>(_args)...));
}

//-----------------------------------------------------------------------------

} // namespace utils

//-----------------------------------------------------------------------------
