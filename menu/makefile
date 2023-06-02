CPP = g++
CPPFLAGS = -Wall -Wextra -std=c++20 -O3 -march=native -finline-functions -funroll-loops -flto
LDFLAGS = -lGL -lglut -lGLU -lm
SRC_DIR = src
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(SRC_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cpp))
BINARY = main

all: $(BINARY)

run: $(BINARY)
	./$^

main: $(OBJECTS)
	$(CPP) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

# Clean up object files and executable
.PHONY: clean clear
clean:
	rm -f $(OBJECTS) $(BINARY)

foda:
	clear && make clean && make && ./$(BINARY)
