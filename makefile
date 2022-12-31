SRC_DIR := ./src
OBJ_DIR := ./obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
CXX := g++
CXXFLAGS := -std=c++23 -O3 -Wall -Wextra
LDFLAGS := -lpthread
INCLUDE := ./include

starforce.exe: $(OBJ_FILES)
	$(CXX) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -I$(INCLUDE) $(CXXFLAGS) -c -o $@ $<

test:
	echo $(SRC_FILES)
	echo $(OBJ_FILES)