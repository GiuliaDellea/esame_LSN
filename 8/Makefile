CC = g++
CFLAGS = -Wall -O3 --std=c++11

es08.exe : es08.o random.o
	$(CC) random.o es08.o -o es08.exe
es08.o : es08.cpp es08.h
	$(CC) -c es08.cpp -o es08.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o es08.exe seed.out
