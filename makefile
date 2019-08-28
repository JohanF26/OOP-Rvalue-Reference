CPPFLAGS= -Wall -Wextra -pedantic -g

all:	Array_test
	# Insert command to compile the code and generate executable

Array_test:	Array_test.o MyInt.o
				g++ $(CPPFLAGS) Array_test.o MyInt.o -o Array_test

Array_test.o:	Array_test.cpp
					g++ -std=c++11 $(CPPFLAGS) -c Array_test.cpp

MyInt.o:	MyInt.cpp
			g++ -std=c++11 $(CPPFLAGS) -c MyInt.cpp

run:	Array_test
		./Array_test

checkmem:	Array_test
			valgrind --leak-check=full ./Array_test

clean:
			rm -f *.o Array_test
