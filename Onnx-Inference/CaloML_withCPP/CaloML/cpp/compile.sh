rm -f main *.o
g++ -std=c++11 -Wall -c gaussian_mixture.cpp
g++ -std=c++11 -Wall -o main gaussian_mixture.o main.cpp
