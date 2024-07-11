# Define the compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
LDFLAGS = -lcryptopp
# Define the target executable
TARGET = output

# Define the source and object files
SRCS = main.cpp src/emp.cpp src/admin.cpp src/crypto.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)



# Rule to link the object files into the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Rule to compile the source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Rule to clean the directory
clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf *.gch
	rm -f $(TARGET)
	rm -f src/*.o
	rm -f src/*.gch

cdata:
	rm -rf data.txt
	rm -rf data/*
	rm -rf key/*