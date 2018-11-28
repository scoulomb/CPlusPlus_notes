#include <boost/type_index.hpp>
#include <utility>
#include <iostream>

#define printType(param) std::cout <<  boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name() << std::endl;

// Case 1: the parameter is a pointer of reference but nor a Forwarding reference.
// 1. If expression is a reference, ignore the reference part
// 2. Then pattern match the type of expression against the type of param to deduce T (and param)

template <typename T>
void f (T& param) // or T*
{
printType(param);
}


template <typename T>
void g (const T& param) // or T*
{
printType(param);
}

// Case 2: the parameter is passed by value.
// 1. If expression is a reference, ignore the reference part
// 2. Then if expression is const or volatile, ignore this modifier
// 3. Then pattern match the type of expression against the type of param to deduce T (and param) -> type of expression = T = Param type



template <typename T>
void h (T param)
{
printType(param);
}

template <typename T>
void hPrim (const T param)
{
printType(param);
}

// Case 3: the parameter is a forwarding reference.
// 1. If expression is an lValue, T and param are deduced to be lValue reference (with const modifiers, volatile most likely too)
// 2. If expression is an RValue, case 1 applies (T is therefore deduced as non reference) (and param type is an RValue reference)

template <typename T>
void i (T&& param)
{
printType(param);
}


template <typename T>
void j (const T&& param)
{
printType(param);
}


int main()
{

int x = 3;
const int cx = x;
const int& rx = x;

std::cout << "Case 1" << std::endl;

f(x); // expression is int, T is int, Param is int&
f(cx); // expression is const int, T is const int, Param is const int&
f(rx); // expression is const int, T is const int, Param is const int&
//f(42);-> can't bind rvalue to ref (non const)

g(x); // expression is int, T is int, Param is const int&
g(cx); // expression is const int, T is int, Param is const int&
g(rx); // expression is const int, T is int, Param is const int&
g(42); // expression is const int (const int && -> const int (cf. 1.)), T is int, Param is const int&

std::cout << "Case 2" << std::endl;

h(x); // expression is int, T is int, Param is int
h(cx); // expression is int, T is int, Param is int
h(rx); // expression is int, T is int, Param is int
h(42); // expression is int, T is int, Param is int

std::cout << "Case 3" << std::endl;

i(x); // LValue, T and param are int&
i(cx); // LValue, T and param are const int&
i(rx); // LValue, T and param are const int&
i(42); // RValue, case 1, expression is int (int&& -> int), T is int, Param is int&&  

std::cout<< "Note 1: 42 is an int not const int, proof" << std::endl; 
printType(42) 

std::cout<< "Note 2: hello is however const, proof" << std::endl; 
printType("hello");
i("hello"); // note const is kept here even if in RValueTest non const version was a better match ??!

std::cout<< "Note 3: here is behavior with const RValue" << std::endl; 
const int&& abc = 42;
printType(abc);
i(abc); // RValue, case 1, expression is const int (const int&& -> const int), T is const int, Param is const int&&  : NO
// This is considered as an LValue, T and param are const int& ??
i(std::forward<const int>(abc)); // later we will see this keep RValue ness

std::cout << "Note 4: Exact form should be T&&" << std::endl;
//j(x);
//j(cx);
//j(rx);
// RValue can't bind an LValue for cases above
j(42); // case 1, expression is int (int&& -> int), expression is int, T is int, Param is const int&&


std::cout << "Same mechanism for auto" << std::endl;
// except initializer list
// not linked to that, only the first one
//int x = 3;
//const int cx = x;
//const int& rx = x;
{
auto x = 3; // h(x)  -> int
const auto cx = x; // same as hPrim(x) -> const int
const auto& rx = x; // g(x) -> const int &
auto&& rrx = x; // i(x) -> int&
//hPrim(x);
printType(x);
printType(cx);
printType(rx);
printType(rrx);
}

std::cout << "Return type can also be deduced" << std::endl;


}
