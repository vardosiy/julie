#pragma once

#include <boost/signals2.hpp>

namespace app {

using Connection		= boost::signals2::connection;
using ScopedConnection	= boost::signals2::scoped_connection;
using ConnectionBlock	= boost::signals2::shared_connection_block;

template<typename Fun>
using SignalMt = boost::signals2::signal<Fun>;

template<typename Fun>
using Signal =
	typename boost::signals2::signal_type<
		Fun,
		boost::signals2::keywords::mutex_type<boost::signals2::dummy_mutex>
	>::type;

} // namespace app
