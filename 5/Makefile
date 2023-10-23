CC = g++
CFLAGS = -Wall -O3 --std=c++11

es05.exe : es05.o random.o
	$(CC) random.o es05.o -o es05.exe
es05.o : es05.cpp
	$(CC) -c es05.cpp -o es05.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o es05.exe seed.out
