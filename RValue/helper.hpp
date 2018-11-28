#include <iostream>
#include <string>

namespace force
{

namespace ref {
void f(std::string& s)
{
std::cout << "force::ref::f(std::string& s): " << s << std::endl;
}

void f(const std::string& s)
{
std::cout << "force::ref::f(const std::string& s): " << s << std::endl;
}


}

namespace constref {
void f(const std::string& s)
{
std::cout << "force::constref::f(const std::string& s): " << s << std::endl;
}
}

namespace refref {
void f(std::string&& s)
{
std::cout << "force::refref::f(std::string&& s): " << s << std::endl;
}
}

namespace constrefref {
void f(const std::string&& s)
{
std::cout << "force::const::refref::f(const std::string&& s): " << s << std::endl;
}
}
}


namespace noRValue
{

/*
void f(std::string s)
{
std::cout << "noRValue::f(std::string s): " << s << std::endl;
}
// => remove would be ambiguate
*/

void f(std::string& s)
{
std::cout << "noRValue::f(std::string& s): " << s << std::endl;
}


void f(const std::string& s)
{
std::cout << "noRValue::f(const std::string& s): " << s << std::endl;
}

}

namespace withRValue
{

void f(std::string& s)
{
std::cout << "withRValue::f(std::string& s): " << s << std::endl;
}


void f(const std::string& s)
{
std::cout << "withRValue::f(const std::string& s): " << s << std::endl;
}

void f(std::string&& s)
{
std::cout << "withRValue::f(std::string&& s): " << s << std::endl;
}


void f(const std::string&& s)
{
std::cout << "withRValue::f(const std::string&& s): " << s << std::endl;
}

}

namespace withRValueButOnlyConstVersion
{

void f(std::string& s)
{
std::cout << "withRValueButOnlyConstVersion::f(std::string& s): " << s << std::endl;
}

void f(const std::string& s)
{
std::cout << "withRValueButOnlyConstVersion::f(const std::string& s): " << s << std::endl;
}

void f(const std::string&& s)
{
std::cout << "withRValueButOnlyConstVersion::f(const std::string&& s): " << s << std::endl;
}

}



