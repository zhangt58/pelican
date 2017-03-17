All: main
#FLAGS = -std=c++11 -Wall
FLAGS = -Wall
main: main.o readinput.o elements.o constants.o
	g++ $(FLAGS) main.o readinput.o elements.o constants.o -o main
main.o: main.cpp
	g++ $(FLAGS) -c main.cpp -o main.o
readinput.o: readinput.cpp readinput.h
	g++ $(FLAGS) -c readinput.cpp -o readinput.o
elements.o: elements.cpp elements.h
	g++ $(FLAGS) -c elements.cpp -o elements.o
constants.o: constants.cpp constants.h
	g++ $(FLAGS) -c constants.cpp -o constants.o
.PHONY: clean
clean:
	-rm constants.o elements.o readinput.o main.o 2> /dev/null
