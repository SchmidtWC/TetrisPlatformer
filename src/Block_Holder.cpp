#include "../include/Block_Holder.h"


void Block_Holder::Rotate(bool direct){
	Blocks[0].rotate(direct);
		Blocks[1].rotate(direct);
		Hit_Boxes[0] = Blocks[0].Box;
		Hit_Boxes[1] = Blocks[1].Box;

/*if(type != 3){
	if(type <= 2) {
		Blocks[0].rotate(direct);
		Blocks[1].rotate(direct);
		Hit_Boxes[0] = Blocks[0].Box;
		Hit_Boxes[1] = Blocks[1].Box;
	}
	else{
		std::cout << 'hagdsfasfasef' << std::endl;
		Blocks[0].rotate(direct);
		Blocks[1].rotate2(direct);
		Hit_Boxes[0] = Blocks[0].Box;
		Hit_Boxes[1] = Blocks[1].Box;
	}
}*/
}

void Block_Holder::Move(int x, int y){
	Blocks[0].move(x, y);
	Blocks[1].move(x, y);
	Hit_Boxes[0] = Blocks[0].Box;
	Hit_Boxes[1] = Blocks[1].Box;
}

void Block_Holder::render(SDL_Renderer* gameRenderer){
	Blocks[0].render(gameRenderer, sprite);
	Blocks[1].render(gameRenderer, sprite);
}
