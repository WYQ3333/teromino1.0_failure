#include"tetromino.h"

HDC hdc;

teromino::teromino(teromino_type index){
	switch (index)
	{
	case I:
		block[0] = { 5, 0 };
		block[1] = { 5, 1 };
		block[2] = { 5, 2 };
		block[3] = { 5, 3 };
		center = { 5, 1.5 };
		type = I;
		break;
	case J:
		block[0] = { 5, 0 };
		block[1] = { 5, 1 };
		block[2] = { 5, 2 };
		block[3] = { 4, 2 };
		center = block[1];
		type = J;
		break;
	case L:
		block[0] = { 5, 0 };
		block[1] = { 5, 1 };
		block[2] = { 5, 2 };
		block[3] = { 6, 2 };
		center = block[1];
		type = L;
		break;
	case O:
		block[0] = { 5, 0 };
		block[1] = { 6, 0 };
		block[2] = { 5, 1 };
		block[3] = { 6, 1 };
		center = { 5.5, 0.5 };
		type = O;
		break;
	case S:
		block[0] = { 6, 0 };
		block[1] = { 5, 0 };
		block[2] = { 5, 1 };
		block[3] = { 4, 1 };
		center = block[1];
		type = S;
		break;
	case Z:
		block[0] = { 4, 0 };
		block[1] = { 5, 0 };
		block[2] = { 5, 1 };
		block[3] = { 6, 1 };
		center = block[1];
		type = Z;
		break;
	case T:
		block[0] = { 4, 0 };
		block[1] = { 5, 0 };
		block[2] = { 6, 0 };
		block[3] = { 5, 1 };
		center = block[1];
		type = T;
		break;
	default:
		break;
	}
}

void teromino::display(){
	for (int i = 0; i < 4; ++i){
		Rectangle(hdc,block[i].X*BORDER, block[i].Y*BORDER, 
			(block[i].X + 1)*BORDER, (block[i].Y + 1)*BORDER);
	}
}
