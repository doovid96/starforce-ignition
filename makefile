CXX=g++
CXXFLAGS=-std=c++23 -O3 -Wall -Wextra
LDFLAGS=-lpthread

starforce.exe: driver.o timer.o starforce.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ driver.o timer.o starforce.o

driver.o: driver.cpp
	$(CXX) $(CXXFLAGS) -c driver.cpp

starforce.o: starforce.cpp
	$(CXX) $(CXXFLAGS) -c starforce.cpp

timer.o: timer.cpp
	$(CXX) $(CXXFLAGS) -c timer.cpp
