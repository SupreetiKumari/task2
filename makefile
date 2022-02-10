all: yourcode.o 
	g++ -Wall -g -o yourcode.out yourcode.o
	
yourcode.o: yourcode.cpp IOuseful.h userfunctions.h filecheck.h
	g++ -c yourcode.cpp	
	
clean:

	rm -f *.o 
	