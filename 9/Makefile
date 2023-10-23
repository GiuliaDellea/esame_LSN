CC = g++
CFLAGS = -Wall -O3 --std=c++11

es09.exe : es09.o random.o cities.o
	$(CC) cities.o random.o es09.o -o es09.exe
es09.o : es09.cpp es09.h
	$(CC) -c es09.cpp -o es09.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
cities.o : cities.cpp cities.h
	$(CC) -c cities.cpp -o cities.o $(CFLAGS)
clean :
	rm *.o es09.exe seed.out
