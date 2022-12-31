CXX=g++
CFLAGS=-std=c++23 -lpthread -O3 -Wall -Wextra

starforce.exe: driver.o timer.o starforce.o
	$(CXX) $(CFLAGS) -o starforce driver.o timer.o starforce.o

driver.o: driver.cpp
	$(CXX) $(CFLAGS) -c driver.cpp

starforce.o: starforce.cpp
	$(CXX) $(CFLAGS) -c starforce.cpp

timer.o: timer.cpp
	$(CXX) $(CFLAGS) -c timer.cpp
