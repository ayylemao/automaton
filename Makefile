# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Files
SRCS = $(wildcard $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Targets
EXECUTABLE = a.out

# Rules
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(EXECUTABLE)

.PHONY: all clean
