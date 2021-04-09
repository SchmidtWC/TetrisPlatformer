// CS 4160 - starter code written by Victor Zordan

#include "../include/GameEngine.h"

int main(int argv, char** args) 
{
  const int SCREEN_WIDTH = 736;
  const int SCREEN_HEIGHT = 480;
  GameEngine engine(SCREEN_WIDTH, SCREEN_HEIGHT);

  engine.my_SDL_init();
  engine.gameLoop();
  

  IMG_Quit();
  SDL_Quit();
  return 0; 
}
