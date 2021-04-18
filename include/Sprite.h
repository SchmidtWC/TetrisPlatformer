#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <functional>
#include <memory>
#include <vector>
#include "../include/Image_Handler.h"

class Sprite {
private:
	SDL_Rect Src_sprite;
	Image_Handler* Images;

	// Sprite sheets information
	std::string sheet_names;
	int Frame_counts;
    int frameWidth;
    int frameHeight;
    SDL_RendererFlip flip;

    SDL_Rect getRect(int frame, int row);


public:
	Sprite(int frame_count, int w, int h,  std::string names, Image_Handler* image) :
			Frame_counts(frame_count), frameWidth(w), frameHeight(h), sheet_names(names), Images(image) {
	}

	void render(SDL_Renderer* renderer, SDL_Rect dest, bool dirct);
    void nextFrame();
    void setFrame(int frame, int row =0);
};