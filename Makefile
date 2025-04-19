# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -Iinclude -pthread

# Directories
SRC_DIR = src
PROJECT_SRC_DIR = src/project
INCLUDE_DIR = include

# Output binary
TARGET = server

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(PROJECT_SRC_DIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link all object files into the final binary
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)
