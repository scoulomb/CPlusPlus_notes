#include <ctime>
#include <ratio>
#include <chrono>
#include <string>

namespace tools
{

// RAII timer 
class Timer {
public:
    Timer(const std::string& name);
    ~Timer();

private:
    std::string _name;
    std::chrono::high_resolution_clock::time_point _start;
};

#define TIMER(name) Timer timer__(name);

}


