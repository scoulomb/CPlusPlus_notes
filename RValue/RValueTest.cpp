#include "helper.hpp"


int main()
{
////////////////////////////////////////
// What is an LValue and RValue?
////////////////////////////////////////

// LValue is something that has an address
std::string str1; // str1 is a LValue
const std::string str2; // str2 is a const LValue

// RValue is something that has NO address
str1 = "hello world"; // "hello world" is a RValue, it is a temporary


// A function() is not necessarily an RValue, if the function returns a reference it is an LValue

////////////////////////////////////////
// What is move?
////////////////////////////////////////

// A move is a transfer of ressource from an object to another object and is more efficient than copying
// Value movement is generally UNSAFE for LValue (object can be reused)
// Value movement is ALWAYS SAFE for RValue (object can not be reused)

////////////////////////////////////////
// How to identify object that can be safely moved
////////////////////////////////////////

// C++ had LValue reference to non const: T&
// std::string& strLVRef1 = "hello"; // error: hello is a RValue // force::ref::f("hello"); // same
std::string& strLVRef2 = str1; force::ref::f(str1);

// C++ had also LValue reference to const: const T&
const std::string& strLVRefToConst1 = "hello"; force::constref::f("hello");// hello is a RValue but reference is const
const std::string& strLVRefToConst2 = str2; force::constref::f(str2); // Note LValue needs to be const
// alternatively std::string const& strLVRefToConstN...

// C++11 (-std=c++11) ADD RValue reference : T&&
const std::string&& strRVRef1 = "hello"; force::refref::f("hello");
// const std::string&& strRValueRef2 = str2; // error str2 is a LValue // force::constrefref::f(str2); // same

// What about const RVRef - No much sense
// They are here to ensure something does not bind to an rvalue.
// http://stackoverflow.com/questions/6307526/c0x-const-rvalue-reference-as-function-parameter
// http://stackoverflow.com/questions/4938875/do-rvalue-references-to-const-have-any-use

// C++11 (-std=c++11) RValue reference to const : const T&&
const std::string&& strRVRef2 = "hello"; force::constrefref::f("hello");
// const std::string&& strRValueRef2 = str2; // error str2 is a LValue
// Same behavior as non const T&&, but assymetry with const T&


// So here are binding rules (and they are similar to affectation rules but mechanism is different)
// Btw affectation rule consistent with the fact that const int& a f() { int a; return a} is fine if return type is const
// const int& a [const T&] = f() [RValue T]; life of local a is extended to the scope of the function call

/*
╔══════════╤════╤══════════╤═════════════╗
║          │ T& │ const T& │ (const) T&& ║
╠══════════╪════╪══════════╪═════════════╣
║ RValue T │ X  │ OK       │ OK          ║
╟──────────┼────┼──────────┼─────────────╢
║ LValue T │ OK │ OK       │ X           ║
╚══════════╧════╧══════════╧═════════════╝

Line = effective parameter
Column = formal parameter

RValue can be bound to RValue ref
LValue cannot be bound to RValue ref

Therefore T&& (RValue reference) binds and identify objects that can be safely moved from
=> cf move operators 



*/

////////////////////////////////////////
// RValue and LValue better match and binding
////////////////////////////////////////

const std::string constHello("constHello");
std::string nonConstHello("nonConstHello");

std::cout << "namespace with non RValue function - As in C++03" << std::endl;
noRValue::f(constHello);
noRValue::f(nonConstHello);
noRValue::f("Tmp hello");
/*
noRValue::f(const std::string& s): constHello
noRValue::f(std::string& s): nonConstHello
noRValue::f(const std::string& s): Tmp hello -> RValue is bound ton const T&
*/

std::cout << "namespace WITH RValue function - C++11" << std::endl;
withRValue::f(constHello);
withRValue::f(nonConstHello);
withRValue::f("Tmp hello");
/*
withRValue::f(const std::string& s): constHello
withRValue::f(std::string& s): nonConstHello
withRValue::f(std::string&& s): Tmp hello -> RValue is bound to T&&
*/


std::cout << "namespace WITH RValue  But Only Const Version function - C++11" << std::endl;
withRValueButOnlyConstVersion::f(constHello);
withRValueButOnlyConstVersion::f(nonConstHello);
withRValueButOnlyConstVersion::f("Tmp hello");
/*
withRValueButOnlyConstVersion::f(const std::string& s): constHello
withRValueButOnlyConstVersion::f(std::string& s): nonConstHello
withRValueButOnlyConstVersion::f(const std::string&& s): Tmp hello ->  RValue is bound to CONST T&&
*/

/*

Better match for effective non const LValue is
T& > const T&
Better match for effective CONST LValue is
const T&

We can see that better match rule for effective RValue (const has no real meaning) is
T&& > const T&& > const T&

It can surprise that for RValue :
- in space with non RValue function, const T& is a better match than T&
- in space with RValue function, T&& is a better match than const T&&

But it makes sense in first case string is const so it matches the const Version
In second case it is still const but intent is to move it so it should not be const
However if there is no T&& we will bind to CONST T&& if present so can be good to delete it

*/

////////////////////////////////////////
// Forcing move
////////////////////////////////////////
std::cout << "Forcing the move" << std::endl;
withRValue::f(nonConstHello);
// we explicitly tell the compiler to move the value because we will not use this object (but the compiler can't guess it)
withRValue::f(std::move(nonConstHello));
// move is a cast http://stackoverflow.com/questions/7509050/the-difference-between-type-casting-and-using-stdmove


// doute affectation OK; surprise seems OK

}
