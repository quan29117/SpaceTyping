OBJ_NAME	=	SpaceTyping

CPP_FILES	=	main.cpp					\
				src/*.cpp					\
				src/ECS/*.cpp				\
				src/ApplicationState/*.cpp	\

CC 	= 	g++ -std=c++17

INCLUDE_PATHS	=	-I include

LIBRARY_PATHS	=	-L lib

LINKER_FLAGS	=	-lmingw32 		\
					-lSDL2main 		\
					-lSDL2_image 	\
					-lSDL2_mixer 	\
					-lSDL2_ttf 		\
					-lSDL2			\

COMPILER_FLAGS	=	-g -Wall -Wextra


all:
	$(CC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CPP_FILES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)