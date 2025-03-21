#kompiliatorius, versija, veliavele
CXX = g++
CXXFLAGS = -O3 -std=c++11

# Define the target executables and source files
TARGETS = vect list deque
SRCS_VECT = V1vect.cpp
SRCS_LIST = V1List.cpp
SRCS_DEQUE = V1deque.cpp

# objektiniai failai
OBJS_VECT = $(SRCS_VECT:.cpp=.o)
OBJS_LIST = $(SRCS_LIST:.cpp=.o)
OBJS_DEQUE = $(SRCS_DEQUE:.cpp=.o)

# Default target
all: $(TARGETS)


vect: $(OBJS_VECT)
	$(CXX) $(CXXFLAGS) -o vect $(OBJS_VECT)


list: $(OBJS_LIST)
	$(CXX) $(CXXFLAGS) -o list $(OBJS_LIST)


deque: $(OBJS_DEQUE)
	$(CXX) $(CXXFLAGS) -o deque $(OBJS_DEQUE)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# išvalymas
clean:
	rm -f $(TARGETS) $(OBJS_VECT) $(OBJS_LIST) $(OBJS_DEQUE)

