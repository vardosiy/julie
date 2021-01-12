#pragma once

#include <chrono>
#include <boost/signals2.hpp>

//-----------------------------------------------------------------------------

namespace jl {
class Object;
class Scene;
}

using ObjectT = jl::Object;
using SceneT = jl::Scene;

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
