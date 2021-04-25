#pragma once

#include <SDL.h> 
#include <SDL_image.h> 
#include <SDL_timer.h>
#include <functional>
#include <memory>
#include <string>

#include "Sprite.h"
#include "Collision.h"

class Game_Entity {
    
	protected:
		std::vector<Hit_Box> Hit_Boxes;
		SDL_Rect destRect;
        Sprite* sprite;
        double velX = 0.0;
        double velY = 0.0;
		bool check_col = true;

	public:
		Game_Entity(int x, int y, int w, int h)
		{
			destRect.x = x;
            destRect.y = y;
            destRect.w = w;
            destRect.h = h;
		}
		~Game_Entity() {}

		double get_velX();
		double get_velY();
		bool get_check_col();
		std::vector<Hit_Box> get_Hit_Boxs();
		void render(SDL_Renderer *gameRenderer);

};