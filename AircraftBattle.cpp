#include<stdio.h>
#include<graphics.h>


enum MyEnum
{
	WIDTH = 450,//背景的高度和宽度
	HEIGHT = 850
};

IMAGE bk;//背景的图片
IMAGE img_role[2];//玩家飞机的图片

struct Plant {
	int x;
	int y;
	bool live;//飞机是否死亡
}player;

//玩家飞机初始化
void playerinit() {
	player.x = WIDTH / 2;
	player.y = WIDTH / 2;
	player.live = true;//true代表存活  false代表死亡
}


//图片初始化
void Loadimg()
{
	//初始化背景图片
	loadimage(&bk, "Resource/images/background.png");
	//初始化飞机图片  数组：0 1
	loadimage(&img_role[0], "Resource/images/hero1.png");
	loadimage(&img_role[1], "Resource/images/hero2.png");
}

//贴图
void gemeDraw() {
	//初始化
	Loadimg();
	//贴背景图
	putimage(0,0,&bk);
	//贴玩家飞机图片    去掉透明背景的二进制：NOTSRCERASE,SRCINVERT(黑色去不掉)
	putimage(WIDTH / 2, WIDTH / 2, &img_role[0], NOTSRCERASE);
	putimage(WIDTH / 2, HEIGHT - 120, &img_role[1], SRCINVERT);
}


//程序的入口
int main()
{

	//游戏窗口的函数

	initgraph(WIDTH, HEIGHT, 1);
	playerinit();
	

	while (1)
	{
		gemeDraw();
	}
	return 0;
}