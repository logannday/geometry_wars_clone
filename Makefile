CXX := g++
OUTPUT := sfmlgame

CXX_FLAGS := -std=c++17 -O3 
INCLUDES := I./src .
LDFLAGS := -O3 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(SRC_FILES: .cpp=.0)

all:$(OUTPUT)

# make main executable
$(OUTPUT):$(OBJ_FILES) Makefile
	$(CXX) $(CXX_FLAGS) $(OBJ_FILES) $(LDFLAGS) -o ./bin/$@

# specifies how obj files are compiled
# the @ defines the naming of -o somehow
.cpp.o:
	$(CXX) -c $(CXX_FLAGS) $(INCLUDES) $< -o $@

run:$(OUTPUT)
	cd bin && ./sfmlgame && cd ..

