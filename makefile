all: cpu

	
cpu: main.o cpu.o
	g++ main.o cpu.o -o cpu

main.o: main.cpp
	g++ -c main.cpp

cpu.o: cpu.cpp
	g++ -c cpu.cpp

clean:
	rm *.o cpu
