#include "../include/Block_Holder.h"


void Block_Holder::Rotate(bool direct){
	Blocks[0].rotate(direct);
	Blocks[1].rotate(direct);
	Hit_Boxes[0] = Blocks[0].Box;
	Hit_Boxes[1] = Blocks[1].Box;
}

void Block_Holder::Move(int x, int y){
	Blocks[0].move(x, y);
	Blocks[1].move(x, y);
	Hit_Boxes[0] = Blocks[0].Box;
	Hit_Boxes[1] = Blocks[1].Box;
}

bool Block_Holder::inside(int x, int y) {
    //Check if mouse is in button
    return (Blocks[0].inside(x, y) || Blocks[1].inside(x, y));
} 

void Block_Holder::render(SDL_Renderer* gameRenderer){
	Blocks[0].render(gameRenderer, sprite);
	Blocks[1].render(gameRenderer, sprite);
}
