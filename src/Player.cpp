#include "../include/Player.h"

void Player::controller(SDL_Event& input){
    //const uint8_t* kbState = SDL_GetKeyboardState(NULL);
    if (input.type == SDL_KEYDOWN) {
		switch (input.key.keysym.sym) {
		case SDLK_a:
			Run_L();
			break;

		case SDLK_d:
			Run_R();
			break;

		case SDLK_SPACE:
			jump();
			break;
		}
	}
	if (input.type == SDL_KEYUP) {
		switch (input.key.keysym.sym) {
		case SDLK_a:
			if (velX < 0){
				stop_run();
			}
			break;

		case SDLK_d:
			if (velX > 0) {
				stop_run();
			}
			break;
		}
	}
}

void Player::updatePos() {
    switch (state) {
		case JUMP:
			jump();
			break;

		case RUN:
			run();
            sprite->nextFrame();
			break;

		case IDLE:
			//idle();
			break;
	}
}

void Player::jump() {
	// Sets Vertical velocity, and Player state to Jump
	if (Jump_Frame == 0 && state != JUMP) {
		Jump_Start = SDL_GetTicks()/ Jump_FR;
		velY = -5;
		state = JUMP;
	}
	
	/*Increases the Y velocity when Jump_Frame modulus 7 = 0,
	  and the Y velocity is less then or equal to 4*/
	else if (Jump_Frame < (SDL_GetTicks() / Jump_FR - Jump_Start) && velY <=4) {
		Jump_Frame = (SDL_GetTicks() / Jump_FR - Jump_Start);
		velY += Gravity;
		if (velY == 0) {
			Gravity = 2;
		}
	}

	//Adjust Player position and boundaries based on the X and Y velocity
	destRect.y += velY;
	destRect.x += velX;
	Hit_Boxes[0].TE = destRect.y;
	Hit_Boxes[0].BE = destRect.y + destRect.h;
	Hit_Boxes[0].LE = destRect.x;
	Hit_Boxes[0].RE = destRect.x + destRect.w;
	Hit_Boxes[1].BE = Hit_Boxes[0].BE - KickH;
    Hit_Boxes[1].TE = Hit_Boxes[1].BE - KickH;
	Hit_Boxes[1].LE = Hit_Boxes[0].LE - KickL;
	Hit_Boxes[1].RE = Hit_Boxes[0].LE;
	Hit_Boxes[2].LE = Hit_Boxes[0].RE;
	Hit_Boxes[2].RE = Hit_Boxes[1].RE + KickL;
	Hit_Boxes[2].BE = Hit_Boxes[0].BE - KickH;
    Hit_Boxes[2].TE = Hit_Boxes[2].BE - KickH;
}

void Player::stop_jump() {
	Gravity = 1;

	//else if the player Velocity X = 0 Set state = Idle
	if (velX == 0) {
		state = IDLE;
	}

	//else set state = Run
	else {
		state = RUN;
	}

	Jump_Frame = 0;
	Jump_Start = 0;
}


/*set Player State = Run, and Player X velocity = 4*/
void Player::Run_R() {
	state = RUN;
	velX = 4;
    left = 0;
}


/*set Player State = Run, and Player X velocity = -4*/
void Player::Run_L() {
	state = RUN;
	velX = -4;
    left = 1;
}


/*Update Player position based on Player X velocity*/
void Player::run() {
	destRect.x += velX;
	Hit_Boxes[0].LE = destRect.x;
	Hit_Boxes[0].RE = destRect.x + destRect.w;
	Hit_Boxes[1].LE = Hit_Boxes[0].LE - KickL;
	Hit_Boxes[1].RE = Hit_Boxes[0].LE;
	Hit_Boxes[2].LE = Hit_Boxes[0].RE;
	Hit_Boxes[2].RE = Hit_Boxes[1].RE + KickL;

}

void Player::stop_run() {
	velX = 0;
	state = IDLE;
}

Hit_Box Player::Kick(){
	return Hit_Boxes[left + 1];
}

void Player::render(SDL_Renderer* renderer) {
    sprite->render(renderer, destRect, !!left);
}