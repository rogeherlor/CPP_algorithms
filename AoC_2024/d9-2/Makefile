# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++20 -Wall -g

# Linker flags
LDFLAGS = -lcurl -lboost_system -lboost_filesystem

# Source and output directories
SRC_DIR = src
BUILD_DIR = build

# Include directories
INCLUDES = -I/usr/include -I$(SRC_DIR)

# Source files
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/fetch_input.cpp

# Object files (stored in the build directory)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Output executable
TARGET = $(BUILD_DIR)/oxo

# Build the target
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile the source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean the generated files
clean:
	rm -rf $(BUILD_DIR)

# Rebuild everything
rebuild: clean $(TARGET)