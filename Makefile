#OBJS specifies which files to compile as part of the project
OBJS = .\src\main.cpp .\src\Game_Engine.cpp .\src\Image_Handler.cpp .\src\Game_Entity.cpp .\src\Sprite.cpp .\src\Player.cpp .\src\Tile.cpp .\src\Collision.cpp \
.\src\Slime.cpp .\src\Button.cpp .\src\Menu.cpp .\src\Block.cpp .\src\Block_Holder.cpp  

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:\SDL2\include\SDL2

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:\SDL2\lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = game

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)


