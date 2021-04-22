#include "Block.h"


void Block::rotate(bool direct) {
	if (direct) {
		if (State == 3) {
			State = 0;
		}
		else {
			State += 1;
		}
	}
	else {
		if (State == 0) {
			State = 3;
		}
		else {
			State -= 1;
		}
	}

	int temp = w;
	w = h;
	h = w;

	if (State == 0) {
		Box.left_edge = Px - offset;
		Box.right_edge = Box.left_edge + w;
		Box.top_edge = Py;
		Box.bottom_edge = Py + h;
	}
	else if (State == 1) {
		Box.left_edge = Px;
		Box.right_edge = Px + w;
		Box.bottom_edge = Py - offset;
		Box.top_edge = Box.bottom_edge - h;
	}
	else if (State == 2) {
		Box.right_edge = Px + offset;
		Box.left_edge = Box.right_edge - w;
		Box.top_edge = Py - h;
		Box.bottom_edge = Py;
	}
	else if (State == 3) {
		Box.left_edge = Px - w;
		Box.right_edge = Px;
		Box.top_edge = Py - offset;
		Box.bottom_edge = Box.top_edge + h;
	}
	dest_rect.x = Box.left_edge;
	dest_rect.y = Box.top_edge;
}

void move(int x, int y){
	Px += x;
	Py += y;
	if (State == 0) {
		Box.left_edge = Px - offset;
		Box.right_edge = Box.left_edge + w;
		Box.top_edge = Py;
		Box.bottom_edge = Py + h;
	}
	else if (State == 1) {
		Box.left_edge = Px;
		Box.right_edge = Px + w;
		Box.bottom_edge = Py - offset;
		Box.top_edge = Box.bottom_edge - h;
	}
	else if (State == 2) {
		Box.right_edge = Px + offset;
		Box.left_edge = Box.right_edge - w;
		Box.top_edge = Py - h;
		Box.bottom_edge = Py;
	}
	else if (State == 3) {
		Box.left_edge = Px - w;
		Box.right_edge = Px;
		Box.top_edge = Py - offset;
		Box.bottom_edge = Box.top_edge + h;
	}
	dest_rect.x = Box.left_edge;
	dest_rect.y = Box.top_edge;
}

void Block::render(SDL_Renderer* gameRenderer) {
	for (int i = 0; i < w / dest_rect.w; i++) {
		sprite->render(gameRenderer, destRect, false);
		dest_rect.x += dest_rect.w;
	}
	dest_rect.y += dest_rect.h;
	for (int i = 1; i < h / dest_rect.h; i++) {
		sprite->render(gameRenderer, destRect, false);
		dest_rect.y += dest_rect.h;
	}

	dest_rect.x = Box.left_edge;
	dest_rect.y = Box.top_edge;
}