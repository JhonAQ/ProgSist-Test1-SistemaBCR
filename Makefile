CXX = g++
CXXFLAGS = -std=c++17 -Isource

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
EXEC = bcr.out

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC)

clean:
	rm -f $(OBJ) $(EXEC)