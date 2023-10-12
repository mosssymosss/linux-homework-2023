
run: main
	./main

complex_number.o: complex_number.cpp complex_number.h
	g++ complex_number.cpp -c

main.o: main.cpp
	g++ main.cpp -c

main: main.o complex_number.o
	g++ main.o complex_number.o -o main


