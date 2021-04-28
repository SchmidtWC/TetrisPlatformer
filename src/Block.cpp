#include "../include/Block.h"


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
		Box.LE = Px - offset;
		Box.RE = Box.LE + w;
		Box.TE = Py;
		Box.BE = Py + h;
	}
	else if (State == 1) {
		Box.LE = Px;
		Box.RE = Px + w;
		Box.BE = Py - offset;
		Box.TE = Box.BE - h;
	}
	else if (State == 2) {
		Box.RE = Px + offset;
		Box.LE = Box.RE - w;
		Box.TE = Py - h;
		Box.BE = Py;
	}
	else if (State == 3) {
		Box.LE = Px - w;
		Box.RE = Px;
		Box.TE = Py - offset;
		Box.BE = Box.TE + h;
	}
	dest_rect.x = Box.LE;
	dest_rect.y = Box.TE;
}

void Block::move(int x, int y){
	Px += x;
	Py += y;
	if (State == 0) {
		Box.LE = Px - offset;
		Box.RE = Box.LE + w;
		Box.TE = Py;
		Box.BE = Py + h;
	}
	else if (State == 1) {
		Box.LE = Px;
		Box.RE = Px + w;
		Box.BE = Py - offset;
		Box.TE = Box.BE - h;
	}
	else if (State == 2) {
		Box.RE = Px + offset;
		Box.LE = Box.RE - w;
		Box.TE = Py - h;
		Box.BE = Py;
	}
	else if (State == 3) {
		Box.LE = Px - w;
		Box.RE = Px;
		Box.TE = Py - offset;
		Box.BE = Box.TE + h;
	}
	dest_rect.x = Box.LE;
	dest_rect.y = Box.TE;
}

#include <iostream>
void Block::render(SDL_Renderer* gameRenderer, Sprite* sprite) {
	std::cout << "x:"<< dest_rect.x << std::endl;
	std::cout << "y:"<< dest_rect.y << std::endl;
	std::cout << "w:"<< dest_rect.w << std::endl;
	std::cout << "h:"<< dest_rect.h << "\n\n\n\n\n"<<std::endl;
	for (int i = 1; i < w / dest_rect.w; i++) {
		std::cout << w / dest_rect.w << std::endl;
		sprite->render(gameRenderer, dest_rect, false);
		dest_rect.x += dest_rect.w;
	}
	dest_rect.y += dest_rect.h;
	for (int i = 1; i < h / dest_rect.h; i++) {
		sprite->render(gameRenderer, dest_rect, false);
		dest_rect.y += dest_rect.h;
	}

	dest_rect.x = Box.LE;
	dest_rect.y = Box.TE;
}
