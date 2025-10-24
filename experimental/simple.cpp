#include "head.hpp"
#include "null_sink.hpp"
#include "null_source.hpp"
#include <boost/ut.hpp>
#include <gnuradio-4.0/BlockRegistry.hpp>
#include <gnuradio-4.0/Graph.hpp>
#include <gnuradio-4.0/Scheduler.hpp>

int main() {
    using namespace boost::ut;

    gr::Graph fg;
    auto&     source = fg.emplaceBlock<gr::packet_modem::NullSource<int>>();
    auto&     head   = fg.emplaceBlock<gr::packet_modem::Head<int>>({{"num_items", 1000UL}});
    auto&     sink   = fg.emplaceBlock<gr::packet_modem::NullSink<int>>();
    expect(eq(gr::ConnectionResult::SUCCESS, fg.connect<"out">(source).to<"in">(head)));
    expect(eq(gr::ConnectionResult::SUCCESS, fg.connect<"out">(head).to<"in">(sink)));

    gr::scheduler::Simple sched;
    if (auto ret = sched.exchange(std::move(fg)); !ret) {
        throw std::runtime_error(std::format("failed to initialize scheduler: {}", ret.error()));
    }
    expect(sched.runAndWait().has_value());

    return 0;
}