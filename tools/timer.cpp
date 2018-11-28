#include "timer.hpp"
#include <iostream>

namespace tools
{

Timer::Timer(const std::string& name)
        : _name(name)
        , _start(std::chrono::high_resolution_clock::now())
{
}

Timer::~Timer()
{
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double> >(
                                                       _start - std::chrono::high_resolution_clock::now());
    std::cout <<  _name + "::It took me " << time_span.count() << " seconds." << std::endl;
}

}

// Inspired from felix.abecassis.me/2011/09/cpp-timer-raii/
// Improved with std::chrono::high_resolution_clock::now()
// http://en.cppreference.com/w/cpp/chrono/high_resolution_clock/now
// http://www.cplusplus.com/reference/chrono/high_resolution_clock/now/

