#pragma once

#include <chrono>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

using clock			= std::chrono::high_resolution_clock;
using timePoint		= std::chrono::time_point<clock>;

using seconds		= std::chrono::seconds;
using milliseconds	= std::chrono::milliseconds;

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
