CXX		  := clang++
CXX_FLAGS := -lSDL2 -lSDL2_Image -Wall -Wextra -std=c++17 -g

BIN		:= bin
SRC		:= src
CLASSES := classes
INCLUDE	:= headers
LIB		:= lib

LIBRARIES	:=
EXECUTABLE	:= main


all: $(BIN)/$(EXECUTABLE)

run: clean all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(CLASSES)/*.cpp $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*