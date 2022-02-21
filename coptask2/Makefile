CFLAGS = -Wall
CC=g++

target1:yourcode.cpp
	$(CC) ${CFLAGS} -g yourcode.cpp -o yourcode.out filecheck.h IO.h userfunctions.h -I /home/parallels/Downloads/subtask2/new/include/ -L /home/parallels/Downloads/subtask2/new/lib/ -lopenblas -lpthread -lgfortran

yourcode.o: yourcode.cpp IOuseful.h userfunctions.h filecheck.h
	$(CC) -c yourcode.cpp
	
.PHONY: clean

clean:
	rm -f *.o yourcode.out
