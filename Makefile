# Theecode makefile for building the project
# Type make in the terminal to build
# Type make BUILD=debug to build using debug flags

CXX = g++

DEBUG_FLAGS = -std=c++20 -g -O0 -Wall -Wextra
RELEASE_FLAGS = -std=c++20 -O3 -DNDEBUG -march=native

BUILD ?= release

ifeq ($(BUILD), debug)
	CXXFLAGS = $(DEBUG_FLAGS)
else
	CXXFLAGS = $(RELEASE_FLAGS)
endif

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

TARGET = theecode.exe

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

clean:
	rm -f obj/*.o $(TARGET)