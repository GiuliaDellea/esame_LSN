CC = g++
CFLAGS = -Wall -O3 --std=c++11

es03.exe : es03.o random.o
	$(CC) random.o es03.o -o es03.exe
es03.o : es03.cpp
	$(CC) -c es03.cpp -o es03.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o es03.exe seed.out
