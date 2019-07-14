#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

//-----------------------------------------------------------------------------

#include <string_view>

#include <boost/format.hpp>

//-----------------------------------------------------------------------------

namespace utils {

//-----------------------------------------------------------------------------

class Logger
{
public:
	static Logger & getInstance();

	template<typename ... Args>
	void log(std::string_view _message, Args && ... _args);

	void setFile(std::string_view _file);

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

inline utils::Logger & logger()
{
	return utils::Logger::getInstance();
}

//-----------------------------------------------------------------------------

#endif // __LOGGER_HPP__
