OBJ_NAME	=	SpaceTyping

CPP_FILES	=	main.cpp						\
				src/*.cpp						\
				src/ECS/*.cpp					\
				src/ECS/Collision/*.cpp			\
				src/ECS/Text/*.cpp				\
				src/ECS/Shoot/*.cpp				\
				src/ApplicationState/*.cpp		\
				src/ApplicationManager/*.cpp	\
				src/UI/*.cpp					\
				src/Math/*.cpp					\

CC 	= 	g++ -std=c++17

INCLUDE_PATHS	=	-I include

LIBRARY_PATHS	=	-L lib -lwinpthread -static-libgcc -static-libstdc++

LINKER_FLAGS	=	-lmingw32 		\
					-lSDL2main 		\
					-lSDL2_image 	\
					-lSDL2_mixer 	\
					-lSDL2_ttf 		\
					-lSDL2			\

all:
	$(CC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CPP_FILES) $(LINKER_FLAGS) -o $(OBJ_NAME)
	$(OBJ_NAME)