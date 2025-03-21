# Define the compiler and compiler flags
CXX = g++
CXXFLAGS = -O3 -std=c++11

# Define the target executables and source files
TARGETS = vect list deque
SRCS_VECT = V1vect.cpp
SRCS_LIST = V1List.cpp
SRCS_DEQUE = V1deque.cpp

# Define the object files
OBJS_VECT = $(SRCS_VECT:.cpp=.o)
OBJS_LIST = $(SRCS_LIST:.cpp=.o)
OBJS_DEQUE = $(SRCS_DEQUE:.cpp=.o)

# Default target
all: $(TARGETS)

# Rule to build the vect executable
vect: $(OBJS_VECT)
	$(CXX) $(CXXFLAGS) -o vect $(OBJS_VECT)

# Rule to build the list executable
list: $(OBJS_LIST)
	$(CXX) $(CXXFLAGS) -o list $(OBJS_LIST)

# Rule to build the deque executable
deque: $(OBJS_DEQUE)
	$(CXX) $(CXXFLAGS) -o deque $(OBJS_DEQUE)

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGETS) $(OBJS_VECT) $(OBJS_LIST) $(OBJS_DEQUE)

# Phony targets
.PHONY: all clean
