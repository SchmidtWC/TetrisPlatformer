#pragma once
#include <cmath>
#include <SDL.h> 
#include <SDL_image.h> 
#include <SDL_timer.h>
#include <string>

#include "Game_Entity.h"
#include "../include/Image_Handler.h"

class Enemy: public Game_Entity{
	protected:
		int gravity = 1;
		int state = IDLE;
		int left = 1;
		int Jump_State = 0;
		int Jump_Start = 0;
		int Jump_FR = 150;

	public:
		static constexpr int IDLE = 0;
        static constexpr int RUN = 1;
        static constexpr int JUMP = 2;

		Enemy(int x, int y, int w, int h, Image_Handler* image, std::string id):
            Game_Entity(x, y, w, h) {
                  sprite = new Sprite(4, 32, 32, id, image);
                  sprite->setFrame(0);

                  Hit_Box Temp; 
                  Temp.LE = destRect.x;
	              Temp.RE = destRect.x + destRect.w;
	              Temp.TE = destRect.y;
	              Temp.BE = destRect.y + destRect.h;
                  Hit_Boxes.push_back(Temp);
            }
}