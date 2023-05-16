CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20
LDFLAGS = -lGL -lglut -lGLU -lm
SRC_DIR = src
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(SRC_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cpp))
BINARY = main

all: $(BINARY)

run: $(BINARY)
	./$^

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and executable
.PHONY: clean clear
clean:
	rm -f $(OBJECTS) $(BINARY)

foda:
	clear && make clean && make && ./$(BINARY)
