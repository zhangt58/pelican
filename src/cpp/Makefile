OPTFLAGS = -O2 -s
PGFLAGS = 
#-pg
DEBUGFLAGS = 
#-g
COMMONFLAGS = -ansi -Wfatal-errors -Wall -Wconversion
CXXFLAGS = $(COMMONFLAGS) $(DEBUGFLAGS) $(OPTFLAGS) $(PGFLAGS)
LINKFLAGS = -lgsl -lgslcblas -lm 
#-static
All: pelican
pelican: main.o readinput.o elements.o constants.o methods.o
	g++ $(CXXFLAGS) main.o readinput.o elements.o constants.o methods.o -o pelican $(LINKFLAGS) 
main.o: main.cpp readinput.h elements.h methods.h
	g++ $(CXXFLAGS) -c main.cpp -o main.o
readinput.o: readinput.cpp readinput.h
	g++ $(CXXFLAGS) -c readinput.cpp -o readinput.o
elements.o: elements.cpp elements.h constants.h
	g++ $(CXXFLAGS) -c elements.cpp -o elements.o
constants.o: constants.cpp constants.h
	g++ $(CXXFLAGS) -c constants.cpp -o constants.o
methods.o: methods.cpp methods.h constants.h elements.h
	g++ $(CXXFLAGS) -c methods.cpp -o methods.o

.PHONY: clean
clean:
	#-rm elements.o readinput.o main.o methods.o constans.o 2> /dev/null
	rm *.o
