#include "../tools/timer.hpp"
#include <iostream>
#include <vector>


struct xxx {

    xxx(long int i)
        : _i(i)
        , _a()
        , _b()
        , _c()
        , _s("This is a string for iteration " + std::to_string(i))
    {
    }

    long int _i;
    long int _a;
    long int _b;
    float _c;
    std::string _s;
};


int main()
{
    // Test iteration time with and without a reserve
    std::cout << "-- Test iteration time with and without a reserve --" << std::endl;

    long int iter = 100000;
    std::vector<xxx> vecInt1;
    std::vector<xxx> vecInt2;

    vecInt1.reserve(iter);
    {
        tools::TIMER("Loop with a reserve"); // initialize timer // Atchung pas timer sinon detruit de suite...
        for (long int i = 0; i < iter; ++i) {
            vecInt1.push_back(xxx(i));
        }

    }

    {
        tools::TIMER("Loop without a reserve"); // initialize timer
        for (long int i = 0; i < iter; ++i) {
            vecInt2.push_back(xxx(i));
        }
    }


    // Test elapsed time for a push at capacity boundary 
    std::cout << "-- Test elapsed time for a push at capacity boundary  --" << std::endl;

    std::vector<xxx> vectInt3;
    
    int fillSize = 29;
    for (int i = 0 ; i < fillSize; ++i) {
        vectInt3.push_back(vectInt3.size());
        std::cout << "size is " << vectInt3.size() << "; capacity is " << vectInt3.capacity() << std::endl;
    }
 

    for (int x = 1 ; x < 7; ++x) {
        {
            tools::TIMER(std::to_string(x) + "::Step Mode"); 

            vectInt3.push_back(xxx(x));
        }
        std::cout << std::to_string(x) + "::size is " << vectInt3.size() << "; capacity is " << vectInt3.capacity() << std::endl;
    }

    return 0;
}
