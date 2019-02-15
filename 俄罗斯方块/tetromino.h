#pragma once 
#include<iostream>
#include<Windows.h>


#include<wingdi.h>    //solidrectangle所在的头文件

using namespace std;

#define BORDER 20  //边界、属性
#define HEIGHT 20  //高
#define WIDTH  20  //宽

//俄罗斯方块的形状
enum teromino_type{
	I,J,L,O,S,Z,T
};

class teromino{
	teromino(teromino_type index);   //构造函数
	teromino_type type;              //定义枚举对象
	int interval = 300;              //定义降落间隔

									//COORD是Windows API中定义的一种结构，
									//表示一个字符在控制台屏幕上的坐标。其定义为：
									//	typedef struct _COORD {
									//		SHORT X; // horizontal coordinate
									//		SHORT Y; // vertical coordinate
									//	} COORD;

	COORD block[4];                  //定义方块的位置
	COORD center;					//定义旋转中心

	void display();					//显示
	void moveLeft();				//向左移动
	void moveRight();				//向右移动
	void moveDown();				//向下移动
	void spin();					//旋转
	void accelerate();				//变速
	void decelerate();				//减速
	bool left();					//最左
	bool right();					//最右

};