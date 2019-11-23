#pragma once

#include "utils/Singleton.hpp"

#include <fstream>

#include <fmt/format.h>

//-----------------------------------------------------------------------------

namespace utils {

//-----------------------------------------------------------------------------

class Logger : public Singleton<Logger>
{
	friend class Singleton<Logger>;

public:
	template<typename ... Args>
	void log(std::string_view _topic, std::string_view _message, Args && ... _args);

private:
	Logger();

	void write(const std::string & _message);
	void writeConsole(const std::string & _message);
	void writeFile(const std::string & _message);

private:
	std::ofstream m_fileStream;

	static constexpr std::string_view k_logFile{ "Log.log" };
};

//-----------------------------------------------------------------------------

template<typename ... Args>
void Logger::log(std::string_view _topic, std::string_view _message, Args && ... _args)
{
	std::string message = fmt::format(_message.data(), std::forward<Args>(_args)...);
	write(fmt::format("{} {}", _topic.data(), message));
}

//-----------------------------------------------------------------------------

} // namespace utils

//-----------------------------------------------------------------------------
