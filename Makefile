all:
	g++ -I include -L lib -o SpaceTyping main.cpp src/ECS/*.cpp src/GameState/*.cpp src/*.cpp -lmingw32 -lSDL2main -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2
	SpaceTyping