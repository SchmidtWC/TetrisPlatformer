#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <functional>
#include <memory>

#include "Game_Entity.h"
#include "Player.h"
#include "Tile.h"

//Window Size in Pixels
static const int SCREEN_WIDTH = 960;
static const int SCREEN_HEIGHT = 768;

/*Collition types
static const char col_left = 'L';
static const char col_top = 'T';
static const char col_bot = 'B';
static const char col_right = 'R';
static const char col_non = 'N';
*/

class Game_Engine {
private:
	std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>> game_window;
    std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>> game_renderer;
	SDL_Event input;
	Image_Handler Images;
	std::fstream Level_file;

	//Game Objects
	Player* player;
	std::vector<Game_Entity> Objects;

	//Particle_Emitter Hive;

	//values to save
	bool Run_game = true;
	int Camera_move = 0;
	int Camera_move_dist = 0;
	int level_height = 0, level_width, tile_size, tile_x, tile_y, tile_type;
	bool col_check;

	//Game Engin Functions
	int Render();
	int Handle_Events();
	int Update_Mechanics();
	int Quit();
	int Level_init();

public:
	Game_Engine();
	int Game_loop();
};