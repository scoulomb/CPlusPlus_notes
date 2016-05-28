# http://gl.developpez.com/tutoriel/outil/makefile/ (changed to CXX)
CXX = g++-4.8
CXXFLAGS = -W -Wall -ansi -pedantic -std=c++11
EXEC = lambda


all: $(EXEC)

# same name in output file and destination for the mrproper
lambda: lambda.o
	$(CXX) -o lambda lambda.o

lambda.o: lambda.cpp
	$(CXX) -o lambda.o -c lambda.cpp $(CXXFLAGS)

clean:
	rm -rf *.o

#clean on same line
mrproper: clean	
	rm -rf $(EXEC)

# http://stackoverflow.com/questions/9123666/command-line-arguments-for-a-program-run-in-a-makefile
run: $(EXEC) 
	./lambda
