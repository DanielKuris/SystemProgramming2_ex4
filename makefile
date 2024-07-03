# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra
LDFLAGS := -pthread  # if needed

# Targets
MAIN := main

# Source files
SRCS := main.cpp tree.cpp
OBJS := $(SRCS:.cpp=.o)
DEPS := $(SRCS:.cpp=.d)

# Main target
$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rules for compiling objects
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include dependency files
-include $(DEPS)

# Generate dependency files
%.d: %.cpp
	$(CXX) $(CXXFLAGS) -MM -MT '$*.o' $< -MF $@

# Clean
clean:
	rm -f $(OBJS) $(DEPS) $(MAIN)

# Phony targets
.PHONY: all clean

all: $(MAIN)

# Default target
.DEFAULT_GOAL := all
