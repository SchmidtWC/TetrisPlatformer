#pragma once
#include <cmath>
#include <SDL.h> 
#include <SDL_image.h> 
#include <SDL_timer.h>
#include <string>

#include "Game_Entity.h"
#include "Image_Handler.h"


class Enemy: public Game_Entity{
	protected:
		int state = IDLE;
		int left = 0;

	public:
		static constexpr int IDLE = 0;
        static constexpr int RUN = 1;

		Enemy(int x, int y, int w, int h, int frame, std::string name, Image_Handler* image):
            Game_Entity(x, y, w, h) {
                  sprite = new Sprite(frame, 32, 32, name, image);
                  sprite->setFrame(0);

                  Hit_Box Temp; 
                  Temp.LE = destRect.x;
	              Temp.RE = destRect.x + destRect.w;
	              Temp.TE = destRect.y;
	              Temp.BE = destRect.y + destRect.h;
                  Hit_Boxes.push_back(Temp);
            }
};