
#include"tetromino.h"
#include<iostream>
#include<thread>
#include<graphics.h >
#include"tetromino.h"

using namespace std;

bool panel[1000][1000];                    //���,true=��,false=ռ��
tetromino *p = nullptr;                     //ͼ��
tetromino *nextp = nullptr;                 //��һ��ͼ��
int score = 0;                                      //����
bool loss;                                              //����Ƿ�ʧ��

void start();                                          //��ʼ
void initpanel();                          //��ʼ�����
void createTetromino();                    //����ͼ��
void play();                               //��������
void eliminate();                          //��������
void goDown(thread&);                    //��������
void control();                            //�������
void endgame();                            //��Ϸ����
bool leftable(const tetromino&);         //��������
bool rightable(const tetromino&);            //��������
bool spinnable(const tetromino&);        //������ת

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

void initpanel()           //��ʼ�����
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			panel[j][i] = true;
		}
	}
}

void createTetromino()     //����ͼ��
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

void play()                                //��������
{
	thread controlThread(control);
	goDown(controlThread);
}

void goDown(thread& thr)                  //��������
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

void control()                             //�������
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

void eliminate()                           //��������
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

void endgame()                             //��Ϸ����
{
	cleardevice();
	closegraph();
	cout << "GAME OVER!" << endl << "YOUR SCORE:" << score << endl;
	system("pause");
	exit(0);
}

void start()                               //��ʼ
{
	initgraph(401, 400);                //��ͼ��ʼ
	char str1[] = "Press any key to start!";
	outtextxy(100, 200, str1);
	char str2[] = "ʹ��WASD�ٿ�";
	outtextxy(100, 300, str2);
	while (!_kbhit());
	cleardevice();
	line(201, 0, 201, 401);           //����
	line(0, 401, 201, 401);           //����
	rectangle(11 * BORDER - 1, 0, 16 * BORDER + 1, 4 * BORDER + 1);                                           //��ʾ��һͼ��
	rectangle(11 * BORDER - 1, 5 * BORDER + 1, 16 * BORDER + 1, 9 * BORDER + 1);                  //��ʾ����  
}

bool leftable(const tetromino& tet)          //��������
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
bool rightable(const tetromino& tet)         //��������
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

bool spinnable(const tetromino& tet)     //������ת
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