#include "../include/Sprite.h"

// get the src rect based on the frame number
SDL_Rect Sprite::getRect(int frame, int row) {
    SDL_Rect r;
    r.w = frameWidth;
    r.h = frameHeight;
    r.x = frameWidth * frame;
    r.y = frameHeight * row;
    return r;
}

void Sprite::nextFrame() {
    int ticks = SDL_GetTicks();
    int currentFrame = (ticks / 100) % Frame_counts;
    Src_sprite = getRect(currentFrame, 0);
}

void Sprite::setFrame(int frame, int row) {
    Src_sprite = getRect(frame, row);
}

void Sprite::render(SDL_Renderer* renderer, SDL_Rect dest, bool dirct) {

	// choosing the direction the sprit faces
	if (dirct) {
		flip = SDL_FLIP_HORIZONTAL;
	}
	else {
		flip = SDL_FLIP_NONE;
	}

	SDL_RenderCopyEx(renderer, Images->get_Texture(sheet_names), &Src_sprite, &dest, 0.0, NULL, flip);
}