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
		//Rectangle是一个函数，使用该函数画一个矩形，可以用当前的画笔画矩形轮廓，
		//用当前画刷进行填充。
		//函数原型：BOOL Rectangle(HDC hdc, int nLeftRect, int nTopRect, 
		//			int nRightRect, int nBottomRect)；
		/*hdc：设备环境句柄。
			nLeftRect：指定矩形左上角的逻辑X坐标。
			nTopRect：指定矩形左上角的逻辑Y坐标。
			nRightRect：指定矩形右下角的逻辑X坐标。
			nBottomRect：指定矩形右下角的逻辑Y坐标。
			返回值：如果函数调用成功，返回值非零，否则返回值为0。
			Windows NT：若想获得更多错误信息，请调用GetLastError函数。
			备注：此函数不使用和改变当前位置。*/
	}
}

void teromino::moveLeft(){  //向左移动
	if (!left())
	{
		for (int i = 0; i < 4; i++)
		{
			clearrectangle(block[i].X*BORDER, block[i].Y*BORDER, (block[i].X + 1)*BORDER, (block[i].Y + 1)*BORDER);
			block[i].X--;
		}
		center.X--;
		display();
	}
}
