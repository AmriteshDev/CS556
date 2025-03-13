CC = g++
CFLAGS = -Wall -O2
OBJ = simulation.o main.o utils.o

all: bank_simulation

bank_simulation: $(OBJ)
	$(CC) $(CFLAGS) -o bank_simulation $(OBJ)

simulation.o: simulation.cpp simulation.h
	$(CC) $(CFLAGS) -c simulation.cpp

main.o: main.cpp simulation.h utils.h
	$(CC) $(CFLAGS) -c main.cpp

utils.o: utils.cpp utils.h
	$(CC) $(CFLAGS) -c utils.cpp

clean:
	rm -f *.o bank_simulation
