# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra
LDFLAGS := -lgtest -lgtest_main -pthread

# Targets
MAIN := main
TEST := test

# Source files
SRCS := main.cpp test.cpp tree.cpp
OBJS := $(SRCS:.cpp=.o)
DEPS := $(SRCS:.cpp=.d)

# Main target
$(MAIN): main.o tree.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# Test target
$(TEST): test.o tree.o
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

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
	rm -f $(OBJS) $(DEPS) $(MAIN) $(TEST)

# Phony targets
.PHONY: all clean

all: $(MAIN) $(TEST)

# Default target
.DEFAULT_GOAL := all
