
#include"tetromino.h"
#include<iostream>
#include<thread>
#include<graphics.h >
#include"tetromino.h"

using namespace std;

bool panel[1000][1000];                    //面板,true=空,false=占据
tetromino *p = nullptr;                     //图形
tetromino *nextp = nullptr;                 //下一个图形
int score = 0;                                      //分数
bool loss;                                              //检测是否失败

void start();                                          //开始
void initpanel();                          //初始化面板
void createTetromino();                    //创造图形
void play();                               //操作方块
void eliminate();                          //消除方块
void goDown(thread&);                    //方块下落
void control();                            //方块控制
void endgame();                            //游戏结束
bool leftable(const tetromino&);         //可以向左
bool rightable(const tetromino&);            //可以向右
bool spinnable(const tetromino&);        //可以旋转

int main(void)
{
	start();
	initpanel();
	while (!loss)
	{
		createTetromino();
		play();
		eliminate();
	}
	endgame();

	return 0;
}

void initpanel()           //初始化面板
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			panel[j][i] = true;
		}
	}
}

void createTetromino()     //创造图形
{
	int choice;
	if (!(panel[0][4] && panel[0][5] && panel[0][6]))
	{
		loss = false;
		endgame();
	}
	if (!nextp)
	{
		srand(time(0));
		choice = rand() % 7;
		switch (choice)
		{
		case I:
			nextp = new tetromino(I);
			break;
		case J:
			nextp = new tetromino(J);
			break;
		case L:
			nextp = new tetromino(L);
			break;
		case O:
			nextp = new tetromino(O);
			break;
		case S:
			nextp = new tetromino(S);
			break;
		case Z:
			nextp = new tetromino(Z);
			break;
		case T:
			nextp = new tetromino(T);
			break;
		}
		p = nextp;
	}
	else
	{
		p = nextp;
	}
	choice = rand() % 7;
	switch (choice)
	{
	case I:
		nextp = new tetromino(I);
		break;
	case J:
		nextp = new tetromino(J);
		break;
	case L:
		nextp = new tetromino(L);
		break;
	case O:
		nextp = new tetromino(O);
		break;
	case S:
		nextp = new tetromino(S);
		break;
	case Z:
		nextp = new tetromino(Z);
		break;
	case T:
		nextp = new tetromino(T);
		break;
	}
	clearrectangle(11 * BORDER, 0, 17 * BORDER, 4 * BORDER);
	for (int i = 0; i < 4; i++)
	{
		solidrectangle((7.5 + nextp->block[i].X)*BORDER, (nextp->block[i].Y)*BORDER, (8.5 + nextp->block[i].X)*BORDER, (1 + nextp->block[i].Y)*BORDER);
	}
	p->display();
}

void play()                                //操作方块
{
	thread controlThread(control);
	goDown(controlThread);
}

void goDown(thread& thr)                  //方块下落
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (!panel[p->block[j].Y + 1][p->block[j].X] || i == HEIGHT - 1)
			{
				for (int k = 0; k < 4; k++)
				{
					panel[p->block[k].Y][p->block[k].X] = false;
				}
				goto JUMPOUT;
			}
		}
		p->moveDown();
		Sleep(p->interval);
	}
JUMPOUT:
	thr.detach();
}

void control()                             //方块控制
{
	while (1)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'w':
				if (spinnable(*p))
				{
					p->spin();
					p->decelerate();
				}
				break;
			case 'a':
				if (leftable(*p))
				{
					p->moveLeft();
					p->decelerate();
				}
				break;
			case 'd':
				if (rightable(*p))
				{
					p->moveRight();
					p->decelerate();
				}
				break;
			case 's':
				p->accelerate();
				break;
			}
		}
	}
}

void eliminate()                           //消除方块
{
	bool flag = true;
	int line = true;
	while (line)
	{
		line = 0;
		for (int i = 0; i < 20; i++)
		{
			flag = true;
			for (int j = 0; j < 10; j++)
			{
				if (panel[i][j])
				{
					flag = false;
				}
			}
			if (flag)
			{
				line = i;
			}
		}
		if (line)
		{
			score++;
			for (int i = line; i > 0; i--)
			{
				for (int j = 0; j < 10; j++)
				{
					panel[i][j] = panel[i - 1][j];
					if (!panel[i][j])
					{
						solidrectangle(j*BORDER, i*BORDER, (j + 1)*BORDER, (i + 1)*BORDER);
					}
					else
					{
						clearrectangle(j*BORDER, i*BORDER, (j + 1)*BORDER, (i + 1)*BORDER);
					}
				}
			}
		}
	}
	clearrectangle(11 * BORDER, 5 * BORDER, 16 * BORDER, 9 * BORDER);
	char str[5];
	sprintf_s(str, "%d", score);
	outtextxy(13 * BORDER, 7 * BORDER, str);
}

void endgame()                             //游戏结束
{
	cleardevice();
	closegraph();
	cout << "GAME OVER!" << endl << "YOUR SCORE:" << score << endl;
	system("pause");
	exit(0);
}

void start()                               //开始
{
	initgraph(401, 400);                //绘图开始
	char str1[] = "Press any key to start!";
	outtextxy(100, 200, str1);
	char str2[] = "使用WASD操控";
	outtextxy(100, 300, str2);
	while (!_kbhit());
	cleardevice();
	line(201, 0, 201, 401);           //竖线
	line(0, 401, 201, 401);           //横线
	rectangle(11 * BORDER - 1, 0, 16 * BORDER + 1, 4 * BORDER + 1);                                           //显示下一图形
	rectangle(11 * BORDER - 1, 5 * BORDER + 1, 16 * BORDER + 1, 9 * BORDER + 1);                  //显示分数  
}

bool leftable(const tetromino& tet)          //可以向左
{
	for (int i = 0; i < 4; i++)
	{
		if (!panel[tet.block[i].Y][tet.block[i].X - 1])
		{
			return false;
		}
	}
	return true;
}
bool rightable(const tetromino& tet)         //可以向右
{
	for (int i = 0; i < 4; i++)
	{
		if (!panel[tet.block[i].Y][tet.block[i].X + 1])
		{
			return false;
		}
	}
	return true;
}

bool spinnable(const tetromino& tet)     //可以旋转
{
	for (int i = 0; i < 4; i++)
	{
		if (!panel[-p->block[i].X + p->center.X + p->center.Y][p->block[i].Y - p->center.Y + p->center.X])
		{
			if (-p->block[i].X + p->center.X + p->center.Y <= 10 && p->block[i].Y - p->center.Y + p->center.X <= 20)
			{
				return false;
			}
		}
	}
	return true;
}