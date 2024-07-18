#include<stdio.h>
#include<graphics.h>

//把图片加载进程序
IMAGE bk;//背景的图片
IMAGE img_role[2];//玩家飞机的图片
IMAGE img_bull[2];//子弹的图片
IMAGE img_enemy[2][2];//敌机图片    大敌机  小敌机


enum MyEnum
{
	WIDTH = 450,//背景的高度和宽度
	HEIGHT = 850,
	BULLET_NUM = 15,
	ENEMY_NUM = 10,
	BIG,
	SMALL
};


//飞机属性
struct Plant {
	int x;
	int y;
	bool live;//飞机是否死亡
	int width;
	int height;
	int hp;//血量
	int type;//类型
}player,bull[BULLET_NUM],enemy[ENEMY_NUM];



//图片初始化
void Loadimg()
{
	//初始化背景图片
	loadimage(&bk, "./Resource/images/background.png");
	//初始化飞机图片  数组：0 1
	loadimage(&img_role[0], "./Resource/images/hero1.png");
	loadimage(&img_role[1], "./Resource/images/hero2.png");
	//子弹的图片
	loadimage(&img_bull[0], "./Resource/images/bullet1.png");
	loadimage(&img_bull[1], "./Resource/images/bullet2.png");
	//敌机图片
	
	//小敌机
	loadimage(&img_enemy[0][0], "./Resource/images/bullet1.png");
	loadimage(&img_enemy[0][1], "./Resource/images/bullet2.png");
	//大敌机
	loadimage(&img_enemy[1][0], "./Resource/images/bullet1.png");
	loadimage(&img_enemy[1][0], "./Resource/images/bullet2.png");
}

//玩家飞机初始化
void playerinit() {
	player.x = WIDTH / 2;
	player.y = HEIGHT - 120;
	player.live = true;//true代表存活  false代表死亡
	//初始化子弹
	for (int i = 0; i < BULLET_NUM; i++)
	{
		bull[i].x = 0;
		bull[i].y = 0;
		bull[i].y = false;
	}
}

//贴图
void gemeDraw() {
	//初始化
	Loadimg();
	//贴背景图
	putimage(0,0,&bk);
	//贴玩家飞机图片    去掉透明背景的二进制：NOTSRCERASE,SRCINVERT(黑色去不掉)
	putimage(player.x, player.y, &img_role[0], NOTSRCERASE);
	putimage(player.x, player.y, &img_role[1], SRCINVERT);

	//绘制子弹
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (bull[i].live)
		{
			putimage(bull[i].x, bull[i].y, &img_bull[0], NOTSRCERASE);
			putimage(bull[i].x, bull[i].y, &img_bull[1], SRCINVERT);
		}
	}
}


//生成子弹
void createBullte() {
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (!bull[i].live)
		{
			bull[i].x = player.x+50;
			bull[i].y = player.y;
			bull[i].live = true;
			//产生了一个子弹就跳出循环
			break;
		}
	}
}

//子弹移动
void BullteMove() {
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (bull[i].live)
		{
			bull[i].y -= 1;
			if (bull[i].y < 0)
			{
				bull[i].live = false;
			}
		}
	}
}

//玩家飞机移动  获取键盘信息：上下左右
void playerMove(int speed) {
	//操作键盘   键盘事件
	//键盘事件： GetAsynKeyState  非阻塞函数，会非常流畅(字母必须用大写)

	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
	{
		if(player.y>0)
		player.y -= speed;
	}
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
	{
		if(player.y+120 < HEIGHT)
		player.y += speed;
	}
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
	{
		if(player.x+40>0)
		player.x -= speed;
	}
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
	{
		if(player.x+60<WIDTH)
		player.x += speed;
	}

	//如果按太快则会生成多个子弹    解决：造成一个延时的效果，使其丝滑一些
	static DWORD t1 = 0, t2 = 0;//静态的二进制变量
	//如果按空格，则生成一个子弹
	if (GetAsyncKeyState(VK_SPACE)&&t2-t1>50)
	{
		createBullte();
		t1 = t2;
	}
	t2 = GetTickCount();
}


//程序的入口
int main()
{

	//游戏窗口的函数

	initgraph(WIDTH, HEIGHT, 1);
	playerinit();
	
	//解决一闪一闪的问题   ->  双缓冲机制:BeginBatchDraw();   FlushBatchDraw();
	BeginBatchDraw();
	while (1)
	{
		gemeDraw();
		FlushBatchDraw();
		playerMove(3);
		BullteMove();
	}
	return 0;
}