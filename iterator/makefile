CXX = g++-4.8
CXXFLAGS = -W -Wall -ansi -pedantic -std=c++11
EXEC = iter_facade_ex


all: $(EXEC)

iter_facade_ex: iter_facade_ex.o
	$(CXX) -o iter_facade_ex iter_facade_ex.o

iter_facade_ex.o: iter_facade_ex.cpp
	$(CXX) -o iter_facade_ex.o -c iter_facade_ex.cpp $(CXXFLAGS)

clean:
	rm -rf *.o

mrproper: clean	
	rm -rf $(EXEC)
