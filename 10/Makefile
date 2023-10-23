CC = mpicxx
CFLAGS = -Wall -O3 --std=c++11

es10.exe : es10.o random.o cities.o
	$(CC) cities.o random.o es10.o -o es10.exe
es10.o : es10.cpp es10.h
	$(CC) -c es10.cpp -o es10.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
cities.o : cities.cpp cities.h
	$(CC) -c cities.cpp -o cities.o $(CFLAGS)
clean :
	rm *.o es10.exe seed.out *.txt
