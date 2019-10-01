#pragma once

#include "Logger.hpp"

//-----------------------------------------------------------------------------

#define LOG(_messageBase, ...) ::utils::Logger::getInstance().log(_messageBase, __VA_ARGS__)

//-----------------------------------------------------------------------------
