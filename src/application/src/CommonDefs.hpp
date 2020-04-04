#pragma once

#include <chrono>
#include <boost/signals2.hpp>

//-----------------------------------------------------------------------------

using Clock			= std::chrono::high_resolution_clock;
using TimePoint		= std::chrono::time_point<Clock>;
using Seconds		= std::chrono::seconds;
using Milliseconds	= std::chrono::milliseconds;

//-----------------------------------------------------------------------------

namespace app {

using Connection		= boost::signals2::connection;
using ScopedConnection	= boost::signals2::scoped_connection;
using ConnectionBlock	= boost::signals2::shared_connection_block;

template<typename Function>
using SignalMt = boost::signals2::signal<Function>;

template<typename Function>
using Signal =
	typename boost::signals2::signal_type<
		Function,
		boost::signals2::keywords::mutex_type<boost::signals2::dummy_mutex>
	>::type;

} // namespace app

//-----------------------------------------------------------------------------
