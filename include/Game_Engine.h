#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include "Game_obj.h"
#include "Player_obj.h"
#include "Background.h"
#include "Particle_Handler.h"

//Window Size in Pixels
//static const int SCREEN_WIDTH = 640;
//static const int SCREEN_HEIGHT = 480;

//Camera movement Boundaries
static const int RIGHT_CAM_BOUND = 480;
static const int LEFT_CAM_BOUND = 160;

static const int fps = 60;
static const int frame_duration = 1000 / fps;
static const int event_duration = 1000 / fps;
static const int update_duration = 1000 / fps;

//Collition types
static const char col_left = 'L';
static const char col_top = 'T';
static const char col_bot = 'B';
static const char col_right = 'R';
static const char col_non = 'N';

//Gournd level
static const int Ground = 450;

class Game_Engine {
private:
	SDL_Window* game_window = NULL;
	SDL_Renderer* game_renderer = NULL;
	SDL_Event input;
	SDL_Rect Window_Rect;
	Image_Handler Images;
	std::fstream Level_file;

	//Game Objects
	std::vector <Game_obj> Objects;
	Game_obj* Level;
	Background background;
	Player_obj Player;
	//Particle_Emitter Hive;

	//values to save
	bool Run_game = true;
	int Camera_move = 0;
	int Camera_move_dist = 0;
	int level_hight = 0, level_length, tile_size, tile_loc, tile_num;
	int Hoffset, Voffset;
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