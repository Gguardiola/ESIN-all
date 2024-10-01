OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: main.o intcell.o
	g++ -o program.exe main.o intcell.o
	rm *.o

solution.exe: main.o intcell.o
	g++ -o solution.exe main.o intcell.o
	rm *.o

main.o: main.cpp intcell.hpp intcell.rep
	g++ -c main.cpp $(OPCIONS)

intcell.o: intcell.cpp intcell.hpp intcell.rep
	g++ -c intcell.cpp $(OPCIONS)

clean:
	rm *.o
	rm *.exe
	rm *.gch
