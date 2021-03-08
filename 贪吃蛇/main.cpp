#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>
#include <conio.h>
#define N		100  //蛇的最大节
#define SIZE	10	//蛇的大小

using namespace std;
//枚举方向 72 80 75 77 上下左右的键值 ASCll码

enum Ch {
	up = 72, 
    down = 80,
	left1 = 75,
	right1 = 77
};


//坐标结构图
struct Coor {
	int x;
	int y;
};

//蛇
struct Snake {
	int n; //当前有多少节
	struct Coor szb[N];  //蛇的坐标
	Ch ch; //方向

};

//随机食物
struct Food {

	struct Coor fzb;		   //坐标
	int			iseat;		  //标记食物是否被吃
};

struct Snake snake;
struct Food  food;

// 初始化蛇
void GameInit() {

	//初始化窗口 SHOWCONSOLE //显示控制台
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
	//初始化食物
	food.iseat = true;
}
//绘制蛇
void DrawSnake() {
	//system("cls");
	cleardevice();
	for (int i = 0; i < snake.n; i++)
	{
		//circle是画圆函数
		//circle(snake.szb[i].x, snake.szb[i].y, 5);
		setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));	//填充图形
		//画矩形
		fillrectangle(snake.szb[i].x, snake.szb[i].y, snake.szb[i].x + SIZE, snake.szb[i].y + SIZE);
	}
	fillrectangle(food.fzb.x, food.fzb.y, food.fzb.x + SIZE, food.fzb.y + SIZE);
}

//蛇的移动
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
//蛇的方向控制
void ChangeCh() {
	char Key; //定义字符
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
//创造食物随机函数
void CreateFood() {
	//srand((unsigned int)time(NULL));
	bool flag;
	while(1){
		flag = 0;
		food.fzb.x = (rand() % 64) * 10;		//窗口的宽 640  乘10 是确保食物在蛇的轨道上
		food.fzb.y = (rand() % 48) * 10;		//窗口的高 480  乘10 是确保食物在蛇的轨道上
		for (int i = 0; i < snake.n; i++) {
			if (snake.szb[i].x == food.fzb.x && snake.szb[i].y == food.fzb.y) {
				flag = 1;
				break;
			}

		}
		if (flag)
			continue;
		else {
			food.iseat = false;  //有新食物
			break;
		}
			
	}

}

//吃食物
void EatFood() {
	if (snake.szb[0].x == food.fzb.x && snake.szb[0].y == food.fzb.y) {
		snake.n++;
		food.iseat = true;
	}
}
//结束条件
int GameOver() {
	//撞墙
	if (snake.szb[0].x < 0 || snake.szb[0].y>640 || snake.szb[0].y < 0 || snake.szb[0].y>480) {
		return 1;
	}
	//吃到自己
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
		while (_kbhit())   //_kbhit() 检测键盘函数 有输入返回1 没有为0
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