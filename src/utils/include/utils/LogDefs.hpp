#pragma once

#include "Logger.hpp"

//-----------------------------------------------------------------------------

#define LOG_INFO(_messageBase, ...)			::utils::Logger::getInstance().log("[INFO]", _messageBase, __VA_ARGS__)
#define LOG_WARNING(_messageBase, ...)		::utils::Logger::getInstance().log("[WARNING]", _messageBase, __VA_ARGS__)
#define LOG_ERROR(_messageBase, ...)		::utils::Logger::getInstance().log("[ERROR]", _messageBase, __VA_ARGS__)
#define LOG_ASSERT(_messageBase, ...)		::utils::Logger::getInstance().log("[ASSERT]", _messageBase, __VA_ARGS__)
#define LOG_EXCEPTION(_messageBase, ...)	::utils::Logger::getInstance().log("[EXCEPTION]", _messageBase, __VA_ARGS__)

//-----------------------------------------------------------------------------
