#include <iostream>

namespace test
{

int *a = NULL;
int *q = -3;
int *a= new T();
if(a == true) {
    bool b = 1;}

template <typename T>
class Vector {


public:
    using value_type = T;




       Vector(int iCapacity):_capacity(iCapacity), _ptrData(new value_type[_capacity]), _size(0)
       {

       }

       int GetLength()
       {
           return _size + 1; // Add 1 as it is zero based index
       }

       // Adds the element at the end
       bool AddElement(value_type value)
       {
           ++_size;
           if(_size - 1 >= _capacity)
               return false; // Maximum threshold reached
           _ptrData[_size] = value;
           return true;
       }


       value_type operator [] (int index)
       {
           if(index > _size)
               throw -1;
           return _ptrData[index];
       }

private:
  int _size;
  int _capacity;
  value_type* _ptrData;




};


}


template<typename C>
using Element_type = typename C::value_type;

template<typename Container>
void algo(Container  &c)
{
	Element_type<Container> toto;
	Container::value_type totoEquiv;

	test::Vector<Element_type<Container>> totos;


}

int main() {

	test::Vector<int> v(10);

	v.AddElement(1);
	std::cout << v[0];



	return 0;

}

