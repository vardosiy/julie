#pragma once

#include <cstdint>
#include <chrono>

//-----------------------------------------------------------------------------

using Clock			= std::chrono::high_resolution_clock;
using TimePoint		= std::chrono::time_point<Clock>;
using Seconds		= std::chrono::seconds;
using Milliseconds	= std::chrono::milliseconds;

using DeltaTime		= Milliseconds;

//-----------------------------------------------------------------------------
namespace jl {
//-----------------------------------------------------------------------------

using s8 = int8_t;
using u8 = uint8_t;

using s16 = int16_t;
using u16 = uint16_t;

using s32 = int32_t;
using u32 = uint32_t;

using s64 = int64_t;
using u64 = uint64_t;

//-----------------------------------------------------------------------------
} // namespace jl
//-----------------------------------------------------------------------------
