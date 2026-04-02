APP = main
CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude -Iheaders
LDFLAGS = -Llib
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
SRC = main.cpp src/game.cpp src/snake.cpp src/food.cpp src/highscore.cpp

all:
	$(CXX) $(SRC) -o $(APP) $(CXXFLAGS) $(LDFLAGS) $(LIBS)

run:
	./$(APP)

clean:
	del $(APP).exe