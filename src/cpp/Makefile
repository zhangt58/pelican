All: main
main: main.o readinput.o elements.o
	g++ main.o readinput.o elements.o -o main
main.o: main.cpp
	g++ -c main.cpp -o main.o
readinput.o: readinput.cpp readinput.h
	g++ -c readinput.cpp -o readinput.o
elements.o: elements.cpp elements.h
	g++ -c elements.cpp -o elements.o
.PHONY: clean
clean:
	-rm elements.o readinput.o main.o 2> /dev/null
