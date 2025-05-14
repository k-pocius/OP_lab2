# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -g -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib
GTEST_LIBS = -lgtest -lgtest_main -pthread

# Target executables
TARGET = V1.5vect
TEST_TARGET = test_V1_5vect

# For deleting the target
TARGET_DEL = V1.5vect.exe

# Source files
SRCS = V1.5vect.cpp

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
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build unit test binary
$(TEST_TARGET): $(TEST_OBJS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TEST_TARGET) $(TEST_OBJS) $(OBJS) $(GTEST_LIBS)

# Compile source files into .o
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run rules
run: $(TARGET)
	./$(TARGET)

run_test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean rule
clean:
	rm -f $(TARGET_DEL) $(TARGET) $(TEST_TARGET) *.o
