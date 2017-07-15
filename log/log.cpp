//
// Created by cj on 12/4/16.
//

#include <boost/log/common.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/core/null_deleter.hpp>

int main()
{
	typedef boost::log::sinks::asynchronous_sink<boost::log::sinks::text_ostream_backend> text_sink;
	boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();
	boost::shared_ptr<std::ostream> stream{&std::clog, boost::null_deleter{}};
	sink->locked_backend()->add_stream(stream);
	boost::log::core::get()->add_sink(sink);

	boost::log::sources::logger lg;
	BOOST_LOG(lg) << "Hello boost log!";
	sink->flush();
}