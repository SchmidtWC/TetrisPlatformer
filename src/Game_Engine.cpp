#include "../include/Game_Engine.h"

/*Constructs the Game Engine*/
Game_Engine::Game_Engine() {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
	}

	IMG_Init(IMG_INIT_PNG);

	game_window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>> (SDL_CreateWindow("Tetris Platformer", 
				SDL_WINDOWPOS_CENTERED, 
				SDL_WINDOWPOS_CENTERED, 
				SCREEN_WIDTH,
				SCREEN_HEIGHT, 0), 
				SDL_DestroyWindow);

    game_renderer = std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>> 
        (SDL_CreateRenderer(game_window.get(), -1, SDL_RENDERER_PRESENTVSYNC), SDL_DestroyRenderer);

	//Init Image Handler
	std::vector <std::string> Image_names = {};

	Images = Image_Handler(Image_names, game_renderer.get());
}


/* Calls Level init
   Then loops through the Game Engine Functions while Run_game = ture
 */
int Game_Engine::Game_loop() {
	//int hold_duration, LST; // LST = Loop Start time

	//Level_init();
	Run_game = true;
	while (Run_game) {
		//LST = SDL_GetTicks();
		Handle_Events();
		Update_Mechanics();
		Render();

		/*/Hold until current frame finishes
		hold_duration = SDL_GetTicks() - LST;
		if (hold_duration < frame_duration) {
			SDL_Delay(frame_duration - hold_duration);
		}*/
	}
	Quit();
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

	return 0;
}


/* Closes the Game Down*/
int Game_Engine::Quit() {
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
	SDL_SetRenderDrawColor(game_renderer.get(), 118, 147, 179, 255);
	SDL_RenderClear(game_renderer.get());

	//Render background and player
	background.Draw(game_renderer.get(), Camera_move);
	Camera_move = 0;
	Player.Draw(game_renderer.get());

	//Loop Through Objects to Render
	for (int i = 0; i < Objects.size(); i++) {
		if (Objects[i].get_is_Rendered()) {
			Objects[i].Draw(game_renderer.get());
		}
	}	

	/*if (Hive.get_is_rendered() || !Hive.get_Done()) {
		Hive.Pe_render(game_renderer);
	}*/

	// Put the Image from the game_renderer to the screen
	SDL_RenderPresent(game_renderer.get());
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
	return 0;
}