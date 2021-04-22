#include "../include/Block_Holder.h"


void Block_Holder::Rotate(){
	Blocks[0].rotate();
	Blocks[1].rotate();
	Hit_Boxes[0] = Blocks[0].Box;
	Hit_Boxes[1] = Blocks[1].Box;
}

void Block_Holder::Move(int x, int y){
	Blocks[0].move(x, y);
	Blocks[1].move(x, y);
	Hit_Boxes[0] = Blocks[0].Box;
	Hit_Boxes[1] = Blocks[1].Box;
}

void render(SDL_Renderer* gameRenderer){
	Blocks[0].render(gameRenderer);
	Blocks[1].render(gameRenderer);
}