#ifndef __LOG_DEFS_HPP__
#define __LOG_DEFS_HPP__

//-----------------------------------------------------------------------------

#include "Logger.hpp"

//-----------------------------------------------------------------------------

#define LOG(_messageBase, ...)												\
	::utils::logger::Logger::getInstance().log(_messageBase, __VA_ARGS__)

//-----------------------------------------------------------------------------

#endif // __LOG_DEFS_HPP__