#include "../include/Tile.h"
#include "../include/Block.h"


struct C_Block {W_1, H_1, R_1, O_1, W_2, H_2, R_2, O_2;};

static const int Block_I = 0;
static const int Block_L = 1;
static const int Block_J = 2;
static const int Block_O = 3;
static const int Block_Z = 4;
static const int Block_S = 5;
static const int Block_T = 6;

class Block_Holder: public Tile{
	private:
		const int move_dist = 32;
		int state = 0;

	protected : 
		C_Block C_Blocks[7];
		std::vector<Block> Blocks;

	public:
		bool active;
		Block_Holder(int Type, int typeTile, int x, int y, int s, int nCols, bool collision, Image_Handler* image, bool act):
		Tile(typeTile, x, y, s, nCols, false, image) {
			active = act;
			check_col = collision;

			int one = s;
			int two = s * 2;
			int three = s * 3;

			C_Blocks[0] = {.W_1 = two, .H_1 = one, .R_1 = 0, .O_1 = 0, .W_2 = two, .H_2 = one, R_2 = 0, .O_2 = two};
			C_Blocks[1] = {.W_1 = two, .H_1 = one, .R_1 = 3, .O_1 = one, .W_2 = two, .H_2 = one, R_2 = 0, .O_2 = 0};
			C_Blocks[2] = {.W_1 = two, .H_1 = one, .R_1 = 1, .O_1 = one, .W_2 = two, .H_2 = one, R_2 = 0, .O_2 = two};
			C_Blocks[3] = {.W_1 = two, .H_1 = one, .R_1 = 0, .O_1 = one, .W_2 = two, .H_2 = one, R_2 = 0, .O_2 = one};
			C_Blocks[4] = {.W_1 = two, .H_1 = one, .R_1 = 0, .O_1 = two, .W_2 = two, .H_2 = one, R_2 = 2, .O_2 = one};
			C_Blocks[5] = {.W_1 = two, .H_1 = one, .R_1 = 2, .O_1 = one, .W_2 = two, .H_2 = one, R_2 = 0, .O_2 = 0};
			C_Blocks[6] = {.W_1 = one, .H_1 = one, .R_1 = 2, .O_1 = 0, .W_2 = three, .H_2 = one, R_2 = 0, .O_2 = two};

			Blocks.push_back(Block(x, y, C_Blocks[Type].W_1, C_Blocks[Type].H_1, s, C_Blocks[Type].R_1, C_Blocks[Type].O_1));
			Blocks.push_back(Block(x, y, C_Blocks[Type].W_2, C_Blocks[Type].H_2, s, C_Blocks[Type].R_2, C_Blocks[Type].O_2));
			Hit_Boxes.push_back(Blocks[0].Box);
			Hit_Boxes.push_back(Blocks[1].Box);
		}

		void Rotate();
		void Move(int x, int y);
};