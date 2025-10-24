add_executable(simple simple.cpp)
target_link_libraries(simple PUBLIC gnuradio-options gnuradio-plugin gnuradio-core magic_enum Boost::ut)