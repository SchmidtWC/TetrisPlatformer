#pragma once

#include "../include/Game_Entity.h"

class Tile: public Game_Entity{
	protected:
		int tileType;
		int numCols;

	public:
		Tile(int typeTile, int x, int y, int s, int nCols, bool collision, Image_Handler* image):
			Game_Entity(x, y, s, s) {
            
            check_col = collision;
            tileType = typeTile;
			numCols = nCols;
			sprite = new Sprite(1, 16, 16, "./asset/tiles.png", image);

			int srcx = (tileType % numCols);
			int srcy = (tileType / numCols);

			sprite->setFrame(srcx, srcy);
		}

		~Tile() {}

		void render(SDL_Renderer* gameRenderer);

};