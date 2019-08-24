#pragma once

#include "utils/Singleton.hpp"

#include <fmt/format.h>

//-----------------------------------------------------------------------------

namespace utils {

//-----------------------------------------------------------------------------

class Logger : public Singleton<Logger>
{
	friend class Singleton<Logger>;

public:
	template<typename ... Args>
	void log(std::string_view _message, Args && ... _args);

	void setFile(std::string_view _file) noexcept;

private:
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
