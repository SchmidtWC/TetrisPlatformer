#pragma once
#include <SDL.h>
#include "Collision.h"

class Block {
private:
	int Px, Py, w, h;
	int offset;

	//int Tile_Size;
	int State = 0;

	SDL_Rect dest_rect;
	Hit_Box Box;

public:
	Block(int Px, int Py, int w, int h, int Tile_Size, int state, int offset): Px(Px), Py(Py), w(w), h(h), State(state), offset(offset){
		dest_rect.w = Tile_Size;
		dest_rect.h = Tile_Size;

		if (state == 0) {
			Box.left_edge = Px - offset;
			Box.right_edge = Box.left_edge + w;
			Box.top_edge = Py;
			Box.bottom_edge = Py + h;
		}
		else if (state == 1) {
			dest_rect.w = h;
			dest_rect.h = w;
			Box.left_edge = Px;
			Box.right_edge = Px + h;
			Box.bottom_edge = Py - offset;
			Box.top_edge = Box.bottom_edge - w;
		}
		else if (state == 2) {
			dest_rect.w = w;
			dest_rect.h = h;
			Box.right_edge = Px + offset;
			Box.left_edge = Box.right_edge - w;
			Box.top_edge = Py - h;
			Box.bottom_edge = Py;
		}
		else if (state == 3) {
			dest_rect.w = h;
			dest_rect.h = w;
			Box.left_edge = Px - h;
			Box.right_edge = Px;
			Box.top_edge = Py - offset;
			Box.bottom_edge = Box.top_edge + w;
		}
		dest_rect.x = Box.left_edge;
		dest_rect.y = Box.top_edge;
	}

	void rotate(bool direct);
	void render(SDL_Renderer* renderer);
};
