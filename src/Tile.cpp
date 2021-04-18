#include "../include/Tile.h"

void Tile::render(SDL_Renderer* gameRenderer){
    sprite->render(gameRenderer, destRect, false);
}