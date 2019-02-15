#pragma once 
#include<iostream>
#include<Windows.h>


#include<wingdi.h>    //solidrectangle���ڵ�ͷ�ļ�

using namespace std;

#define BORDER 20  //�߽硢����
#define HEIGHT 20  //��
#define WIDTH  20  //��

//����˹�������״
enum teromino_type{
	I,J,L,O,S,Z,T
};

class teromino{
	teromino(teromino_type index);   //���캯��
	teromino_type type;              //����ö�ٶ���
	int interval = 300;              //���彵����

									//COORD��Windows API�ж����һ�ֽṹ��
									//��ʾһ���ַ��ڿ���̨��Ļ�ϵ����ꡣ�䶨��Ϊ��
									//	typedef struct _COORD {
									//		SHORT X; // horizontal coordinate
									//		SHORT Y; // vertical coordinate
									//	} COORD;

	COORD block[4];                  //���巽���λ��
	COORD center;					//������ת����

	void display();					//��ʾ
	void moveLeft();				//�����ƶ�
	void moveRight();				//�����ƶ�
	void moveDown();				//�����ƶ�
	void spin();					//��ת
	void accelerate();				//����
	void decelerate();				//����
	bool left();					//����
	bool right();					//����

};