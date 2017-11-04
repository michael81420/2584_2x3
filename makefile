all:
	g++ -std=c++0x -O3 -g -Wall -fmessage-length=0 -o 2584sol 2584sol.cpp 
clean:
	rm 2584sol