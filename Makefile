# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -g -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib
GTEST_LIBS = -lgtest -lgtest_main -pthread

# Target executables
TARGET = V1_5vect
TEST_TARGET = test_V1_5vect

# Source files
SRCS = V1.5vect.cpp V1.5main.cpp

# Header files
HEADERS = lib.h V1.5vect.h

# Object files
OBJS = $(SRCS:.cpp=.o)

# Test files
TEST_SRCS = test_V1_5vect.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Default rule builds both app and test
all: $(TARGET) $(TEST_TARGET)

# Rule to build main app
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Rule to build unit test binary
$(TEST_TARGET): $(TEST_OBJS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(TEST_OBJS) $(OBJS) $(GTEST_LIBS)

# Compile source files into .o
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run app
run: $(TARGET)
	./$(TARGET)

# Run tests
run_test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean build
clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o
