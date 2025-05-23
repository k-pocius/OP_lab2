# Makefile for V1.5 project with Google Test

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = program
TEST_TARGET = test_student

# Main program source & object files
MAIN_SRC = V1.5main.cpp V1.5vect.cpp
MAIN_OBJ = V1.5main.o V1.5vect.o

# Test source & object files
TEST_SRC = test_V1_5vect.cpp V1.5vect.cpp
TEST_OBJ = test_V1_5vect.o V1.5vect_test.o

# Default target
all: $(TARGET)

# Build main program
$(TARGET): $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(MAIN_OBJ)

V1.5main.o: V1.5main.cpp V1.5vect.h
	$(CXX) $(CXXFLAGS) -c V1.5main.cpp

V1.5vect.o: V1.5vect.cpp V1.5vect.h
	$(CXX) $(CXXFLAGS) -c V1.5vect.cpp

# Build test executable
$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJ) $(LDFLAGS)


test_V1_5vect.o: test_V1_5vect.cpp V1.5vect.h
	$(CXX) $(CXXFLAGS) -c test_V1_5vect.cpp -o test_V1_5vect.o

V1.5vect_test.o: V1.5vect.cpp V1.5vect.h
	$(CXX) $(CXXFLAGS) -c V1.5vect.cpp -o V1.5vect_test.o

# Add these paths if using Homebrew
INCLUDES = -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lgtest -lgtest_main -pthread

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra $(INCLUDES)

# Run main program
run: $(TARGET)
	./$(TARGET)

# Run test suite only
run_test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Cleanup
clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o
