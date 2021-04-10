#include "Game_Engine.h"

/*Constructs the Game Engine*/
Game_Engine::Game_Engine() {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
	}

	IMG_Init(IMG_INIT_PNG);

	game_window = SDL_CreateWindow("Forest Bear", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	game_renderer = SDL_CreateRenderer(game_window, -1, 0);

	Window_Rect.x = 0;
	Window_Rect.y = 0;
	Window_Rect.w = 640;
	Window_Rect.h = 480;

	//Init Image Handler
	std::vector <std::string> Image_names = { 
		"Layer2.png", "Layer3.png", "Layer4.png", "Layer5.png", "Layer6.png", 
		"Layer7.png", "Layer8.png", "Layer9.png", "Level_tile_sheet.png", 
		"Idle.png", "run.png", "jump.png" };

	Images = Image_Handler(Image_names, game_renderer);
}


/* Calls Level init
   Then loops through the Game Engine Functions while Run_game = ture
 */
int Game_Engine::Game_loop() {
	int hold_duration, LST; // LST = Loop Start time

	Level_init();
	Run_game = true;
	while (Run_game) {
		LST = SDL_GetTicks();
		Handle_Events();
		Update_Mechanics();
		Render();

		//Hold until current frame finishes
		hold_duration = SDL_GetTicks() - LST;
		if (hold_duration < frame_duration) {
			SDL_Delay(frame_duration - hold_duration);
		}
	}
	return 0;
}


/* Constructs Objects in the Level
   Objects Include:
		- Level Boundary Rect
		- Background Rect
		- Wall Rects
		- Player
*/
int Game_Engine::Level_init() {
	SDL_Rect DestRect, src_rect;

	//Read tile and level dementions
	Level_file.open("tile_Sheet.txt");
	if (Level_file.is_open()){
		Level_file >> level_hight;
		Level_file >> level_length;
		Level_file >> tile_size;
	}

	//Level bound
	DestRect.x = 0;
	DestRect.y = 0;
	DestRect.h = 0;
	DestRect.w = tile_size * level_length;
	Level = new Game_obj(DestRect, &Images, 0, true, "");

	//Read level tile sheet layout
	if (Level_file.is_open()) {
		while (!Level_file.eof()) {
			Level_file >> tile_loc;
			Level_file >> tile_num;
			Level_file >> col_check;
			Level_file >> Hoffset;
			Level_file >> Voffset;

			DestRect.x = (tile_loc % level_length) * tile_size + Hoffset;
			DestRect.y = tile_loc/level_length * tile_size + Voffset;
			DestRect.w = tile_size;
			DestRect.h = tile_size;

			//create objects at the specified locations
			Objects.push_back(Game_obj(DestRect, &Images, tile_num, col_check, "Level_tile_sheet.png"));
		}
	}

	//Background
	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.h = SCREEN_HEIGHT;
	src_rect.w = SCREEN_WIDTH;

	DestRect.x = SCREEN_WIDTH;
	DestRect.y = 0;
	DestRect.h = SCREEN_HEIGHT;
	DestRect.w = SCREEN_WIDTH;

	std::vector <SDL_Rect> Src_rect = { src_rect, DestRect };
	std::vector <std::string> TRX_names = { "Layer2.png", "Layer3.png", "Layer4.png", "Layer5.png", "Layer6.png", "Layer7.png", "Layer8.png", "Layer9.png" };
	background = Background(Src_rect, TRX_names, &Images);


	//Player Character
	DestRect.x = 170;
	DestRect.y = 366;
	DestRect.h = 60;
	DestRect.w = 40;
	std::vector <int> frame_count = {1, 6, 3};
	std::vector <int> duration = {1, 110, 100};
	std::vector <std::string> names = {"Idle.png", "run.png", "jump.png"};
	Player = Player_obj(DestRect, &Images,
						frame_count, duration, names);

	/*DestRect.x = 71;
	DestRect.y = 500;
	DestRect.h = 71;
	DestRect.w = 71;
	src_rect.h = 0;
	src_rect.w = 0;
	std::string emitter = " dd";
	std::string particle = " pd";
	//Particle_Emitter(DestRect, &Images, src_rect, emitter, particle);
	Hive = Particle_Emitter(DestRect, &Images, src_rect, emitter, particle);*/

	return 0;
}


/* Closes the Game Down*/
int Game_Engine::Quit() {
	SDL_DestroyRenderer(game_renderer);
	SDL_DestroyWindow(game_window);

	IMG_Quit();
	SDL_Quit();
	return 0;
}


/* Clears Last Render
   Then Renders:
		- Objects
		- Background
		- Player

   Putes the Resulting image to the window
*/
int Game_Engine::Render() {

	//clear last Render
	SDL_SetRenderDrawColor(game_renderer, 118, 147, 179, 255);
	SDL_RenderClear(game_renderer);

	//Render background and player
	background.Draw(game_renderer, Camera_move);
	Camera_move = 0;
	Player.Draw(game_renderer);

	//Loop Through Objects to Render
	for (int i = 0; i < Objects.size(); i++) {
		if (Objects[i].get_is_Rendered()) {
			Objects[i].Draw(game_renderer);
		}
	}	

	/*if (Hive.get_is_rendered() || !Hive.get_Done()) {
		Hive.Pe_render(game_renderer);
	}*/

	// Put the Image from the game_renderer to the screen
	SDL_RenderPresent(game_renderer);
	return 0;
}

// Handles all user Input
int Game_Engine::Handle_Events() {
	SDL_Event input;
	SDL_PollEvent(&input);

	if (input.type == SDL_QUIT) Run_game = false;

	/* Calls Player movemet Functions when a key is pressed
		Jump : Space
		Run Left : A
		Run Right : D
		
		Calls Player Functions to end end actions when there repective Key is relesed
	*/

	if (input.type == SDL_KEYDOWN) {
		switch (input.key.keysym.sym) {
		case SDLK_a:
			Player.Run_L();
			break;

		case SDLK_d:
			Player.Run_R();
			break;

		case SDLK_SPACE:
			Player.jump();
			break;
		}
	}
	if (input.type == SDL_KEYUP) {
		switch (input.key.keysym.sym) {
		case SDLK_a:
			if (Player.get_Vel_x() < 0){
				Player.stop_run();
			}
			break;

		case SDLK_d:
			if (Player.get_Vel_x() > 0) {
				Player.stop_run();
			}
			break;
		}
	}
	return 0;
}


/* Updates the Player and Game Object Positions
   Checks For collitions between the Player Character and:
		-Gmae objects
		-Camera boundaries
*/
int Game_Engine::Update_Mechanics() {

	// Get Player State and call the coresponding Player Position update function
	switch (Player.get_State()) {
	case Jump:
		Player.jump();
		break;

	case Run:
		Player.run();
		break;

	case Idle:
		Player.idle();
		break;
	}

	//move camera based on Player collitions with Camera Bounds
	Camera_move_dist = 0;

	// Check for collitions with Left Camera Bound
	if (Player.get_edge_L() < LEFT_CAM_BOUND && Level->get_edge_L() != Window_Rect.x) {
		if (Player.get_Vel_x() <= Level->get_edge_L()) {
			Camera_move_dist = Window_Rect.x - Level->get_edge_L();
			if (Level->get_edge_L() == -8) {
				Camera_move_dist = -8;
			}
			Level->Move_side(Camera_move_dist);
			Player.cam_col_left(LEFT_CAM_BOUND);
		}
		else {
			Camera_move_dist = Player.get_edge_L() - LEFT_CAM_BOUND;
			if (Level->get_edge_L() == -8) {
				Camera_move_dist = -8;
			}
			Level->Move_side(Camera_move_dist);
			Player.cam_col_left(LEFT_CAM_BOUND);
		}
		for (int i = 0; i < Objects.size(); i++) {
			Objects[i].Move_side(Camera_move_dist);
		}
		Camera_move = Camera_move_dist;
		Camera_move_dist = 0;
	}

	// Check for collition with Right Camera Bound
	if (Player.get_edge_R() > RIGHT_CAM_BOUND && Level->get_edge_R() != Window_Rect.w) {
		if (Player.get_Vel_x() > Level->get_edge_R() - Window_Rect.w) {
			Camera_move_dist = Level->get_edge_R() - Window_Rect.w;
				Level->Move_side(Camera_move_dist);
				Player.cam_col_right(RIGHT_CAM_BOUND);
		}
		else {
			Camera_move_dist = Player.get_edge_R() - RIGHT_CAM_BOUND;
				Level->Move_side(Camera_move_dist);
				Player.cam_col_right(RIGHT_CAM_BOUND);
		}
		for (int i = 0; i < Objects.size(); i++) {
			Objects[i].Move_side(Camera_move_dist);
		}
		Camera_move = Camera_move_dist;
		Camera_move_dist = 0;
	}

	//checks if an object is within the window
	bool render = true;
	for (int i = 0; i < Objects.size(); i++) {
		if (Objects[i].get_edge_R() < Window_Rect.x && 
			Objects[i].get_edge_L() > (Window_Rect.x + Window_Rect.w)) {
			bool render = false;
		}
		else if (Objects[i].get_edge_T() > (Window_Rect.y + Window_Rect.h) &&
				 Objects[i].get_edge_B() < Window_Rect.y) {
			bool render = false;
		}

		Objects[i].set_is_Rendered(render);
		render = true;
	}

	/*if (!Hive.get_is_rendered() && !Hive.get_Done()) {
		Hive.Pe_update();
	}

	if (Collision_check(Player.get_Hitbox(), Hive.get_HitBox())) {
		Hive.Pe_update();
	}*/
	
	int temp_B, temp_S;
	char col_type = ' ';
	const char col_T = 'T';
	const char col_B = 'B';
	const char col_L = 'L';
	const char col_R = 'R';
	const char col_N = ' ';

	/*Collitions*/
	for (int i = 0; i < Objects.size(); i++) {
		if (Objects[i].get_check_col()) {
			temp_B = Player.get_edge_B() - Objects[i].get_edge_T();
			temp_S = Player.get_edge_R() - Objects[i].get_edge_L();
			if (Collision_check(Player.get_Hitbox(), Objects[i].get_Hitbox())) {
				temp_B = Player.get_edge_B() - Objects[i].get_edge_T();
				temp_S = Player.get_edge_R() - Objects[i].get_edge_L();
				if (Player.get_edge_B() - Objects[i].get_edge_T() <= 6) {
					/*if (!(Player.get_edge_R() - Objects[i].get_edge_L() <= 4)) {
						col_type = col_B;
					}
					else if (!(Objects[i].get_edge_R() - Player.get_edge_L() <= 4)) {
						col_type = col_B;
					}*/
					col_type = col_B;
					/*Player.col_bot(Objects[i].get_edge_T() - 2);
					Player.stop_jump();*/
				}
				else if (Player.get_edge_R() - Objects[i].get_edge_L() <= 4) {
					col_type = col_L;
					//Player.col_left(Objects[i].get_edge_L());
				}
				else if (Objects[i].get_edge_R() - Player.get_edge_L() <= 4) {
					col_type = col_R;
					//Player.col_right(Objects[i].get_edge_R());
				}
				else if (Objects[i].get_edge_B() - Player.get_edge_T() <= 6) {
					/*if (!(Player.get_edge_R() - Objects[i].get_edge_L() <= 4)) {
						col_type = col_T;
					}
					else if (!(Objects[i].get_edge_R() - Player.get_edge_L() <= 4)) {
						col_type = col_T;
					}*/
					col_type = col_T;
					//Player.col_top(Objects[i].get_edge_B());
				}
				else {
					col_type = col_N;
					/*if (Player.get_edge_B() != Objects[i].get_edge_T()) {
						Player.set_State(Jump);
					}*/
				}
			}

			switch (col_type) {
			case col_B:
				Player.col_bot(Objects[i].get_edge_T());
				Player.stop_jump();
				break;
			case col_L:
				Player.col_left(Objects[i].get_edge_L()-1);
				break;
			case col_R:
				Player.col_right(Objects[i].get_edge_R()+1);
				break;
			case col_T:
				Player.col_top(Objects[i].get_edge_B());
				break;
			default:
				if (Player.get_edge_B() != Objects[i].get_edge_T()) {
					Player.set_State(Jump);
					break;
				}
			}
			//std::cout << col_type << std::endl;
			col_type = col_N;
		}
	}


	
	return 0;
}