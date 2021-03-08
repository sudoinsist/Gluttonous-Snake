#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>
#include <conio.h>
#define N		100  //�ߵ�����
#define SIZE	10	//�ߵĴ�С

using namespace std;
//ö�ٷ��� 72 80 75 77 �������ҵļ�ֵ ASCll��

enum Ch {
	up = 72, 
    down = 80,
	left1 = 75,
	right1 = 77
};


//����ṹͼ
struct Coor {
	int x;
	int y;
};

//��
struct Snake {
	int n; //��ǰ�ж��ٽ�
	struct Coor szb[N];  //�ߵ�����
	Ch ch; //����

};

//���ʳ��
struct Food {

	struct Coor fzb;		   //����
	int			iseat;		  //���ʳ���Ƿ񱻳�
};

struct Snake snake;
struct Food  food;

// ��ʼ����
void GameInit() {

	//��ʼ������ SHOWCONSOLE //��ʾ����̨
	//initgraph(640, 480,SHOWCONSOLE);
	initgraph(640, 480);
	srand((unsigned int)time(NULL));
	snake.n = 3;
	snake.ch = right1;
	snake.szb[0].x = 100;
	snake.szb[0].y = 100;
	snake.szb[0].x = 90;
	snake.szb[0].y = 100;
	snake.szb[0].x = 80;
	snake.szb[0].y = 100;
	//��ʼ��ʳ��
	food.iseat = true;
}
//������
void DrawSnake() {
	//system("cls");
	cleardevice();
	for (int i = 0; i < snake.n; i++)
	{
		//circle�ǻ�Բ����
		//circle(snake.szb[i].x, snake.szb[i].y, 5);
		setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));	//���ͼ��
		//������
		fillrectangle(snake.szb[i].x, snake.szb[i].y, snake.szb[i].x + SIZE, snake.szb[i].y + SIZE);
	}
	fillrectangle(food.fzb.x, food.fzb.y, food.fzb.x + SIZE, food.fzb.y + SIZE);
}

//�ߵ��ƶ�
void SankeMove() {
	for (int i = snake.n - 1; i > 0; i--) {
		snake.szb[i].x = snake.szb[i - 1].x;
		snake.szb[i].y = snake.szb[i - 1].y;
	}
	switch (snake.ch)
	{
	case up:
		snake.szb[0].y -= SIZE; break;
	case down:
		snake.szb[0].y += SIZE; break;
	case left1:
		snake.szb[0].x -= SIZE; break;
	case right1:
		snake.szb[0].x += SIZE; break;
	}
}
//�ߵķ������
void ChangeCh() {
	char Key; //�����ַ�
	Key = _getch();
	switch (Key)
	{
	case up:
		if(snake.ch != down)
		snake.ch = up; break;
	case down:
		if (snake.ch != up)
		snake.ch = down; break;
	case left1:
		if (snake.ch != right1)
		snake.ch = left1; break;
	case right1:
		if (snake.ch != left1)
		snake.ch =right1; break;
	}
}
//����ʳ���������
void CreateFood() {
	//srand((unsigned int)time(NULL));
	bool flag;
	while(1){
		flag = 0;
		food.fzb.x = (rand() % 64) * 10;		//���ڵĿ� 640  ��10 ��ȷ��ʳ�����ߵĹ����
		food.fzb.y = (rand() % 48) * 10;		//���ڵĸ� 480  ��10 ��ȷ��ʳ�����ߵĹ����
		for (int i = 0; i < snake.n; i++) {
			if (snake.szb[i].x == food.fzb.x && snake.szb[i].y == food.fzb.y) {
				flag = 1;
				break;
			}

		}
		if (flag)
			continue;
		else {
			food.iseat = false;  //����ʳ��
			break;
		}
			
	}

}

//��ʳ��
void EatFood() {
	if (snake.szb[0].x == food.fzb.x && snake.szb[0].y == food.fzb.y) {
		snake.n++;
		food.iseat = true;
	}
}
//��������
int GameOver() {
	//ײǽ
	if (snake.szb[0].x < 0 || snake.szb[0].y>640 || snake.szb[0].y < 0 || snake.szb[0].y>480) {
		return 1;
	}
	//�Ե��Լ�
	for (int i = snake.n-1; i > 0; i--) {
		if (snake.szb[0].x == snake.szb[i].x && snake.szb[0].y == snake.szb[i].y) {
			return 1;
		}
	}
}

int main() {
	GameInit();
	while (1)
	{
		while (_kbhit())   //_kbhit() �����̺��� �����뷵��1 û��Ϊ0
		{
			ChangeCh();
		}
		if (food.iseat == true)
				CreateFood();
			SankeMove();
			DrawSnake();
			EatFood();
			Sleep(80);
			if (GameOver())
				break;
		
	}
	
	
	return 0;
}