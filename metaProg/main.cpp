#include "../tools/timer.hpp"
#include <iostream>
#include <vector>

# define number 10

template<long long int N> // add long long
class Factorial {
public:
    enum { value = N * Factorial<N-1>::value };
};

template <> // add template <>
class Factorial<1> {
public:
    enum { value = 1 };
};



int factorialR(int n) {

    if(n <= 1) 
    {
        return 1;
    }
    return n * factorialR(n - 1);

}

int factorialI( int n)
{
    int res = 1;
    for (int j=1; j<=n; ++j)
    {
       res *= j;
    }
    return res;
}




int main()
{
   
   int res; 

   {
        tools::TIMER("Factorial iterative"); 
        res = factorialI(number);

    }
    std::cout << res << std::endl;

   {
        tools::TIMER("Factorial recursive"); 
        res = factorialR(number);

    }
    std::cout << res << std::endl;


    {
        tools::TIMER("Factorial metaProg"); 
        res = Factorial<number>::value;

    }
    std::cout << res << std::endl;

    return 0;
}
