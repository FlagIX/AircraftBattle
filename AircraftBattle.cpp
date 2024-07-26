#include<stdio.h>
#include<graphics.h>
#include <time.h>
//把图片加载进程序
IMAGE bk;//背景的图片
IMAGE img_role[2];//玩家飞机的图片
IMAGE img_bull[2];//子弹的图片
IMAGE img_enemy[2][2];//敌机图片    大敌机  小敌机


enum MyEnum
{
	WIDTH = 450,//背景的高度和宽度
	HEIGHT = 850,
	BULLET_NUM = 100,
	ENEMY_NUM = 5,
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
	loadimage(&img_enemy[0][0], "./Resource/images/enemy1.png");
	loadimage(&img_enemy[0][1], "./Resource/images/a0b71bfc88cf49cf9abbc42229ca9d22.png");
	//大敌机
	loadimage(&img_enemy[1][0], "./Resource/images/enemy3_n1.png");
	loadimage(&img_enemy[1][1], "./Resource/images/enemy3_n2.png");
}


//生产飞机
void enemyHP(int i) {
	//大飞机和小飞机是不一样的
	if (rand()%8)//1->8都有可能
	{
		enemy[i].type = SMALL;
		enemy[i].hp = 1;
		enemy[i].width = 156;
		enemy[i].height = 108;
	}
	else
	{
		enemy[i].type = BIG;
		enemy[i].hp = 3;
		enemy[i].width = 156;//测量飞机图片
		enemy[i].height = 108;
	}
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
	//初始化敌机
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//敌机没有
		enemy[i].live = false;
		//生产飞机
		enemyHP(i);
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
	putimage(player.x, player.y, &img_role[1], NOTSRCERASE);

	//绘制子弹
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (bull[i].live)
		{
			putimage(bull[i].x, bull[i].y, &img_bull[0]);
			putimage(bull[i].x, bull[i].y, &img_bull[1]);
			rectangle(bull[i].x, bull[i].y, bull[i].x + 10, bull[i].y + 20);
		}
	}

	//绘制敌机
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy[i].live)
		{
			if (enemy[i].type = BIG)
			{
				//绘制大敌机
				putimage(enemy[i].x, enemy[i].y, &img_enemy[1][0], NOTSRCERASE);
				putimage(enemy[i].x, enemy[i].y, &img_enemy[1][1], NOTSRCERASE);
				rectangle(enemy[i].x, enemy[i].y, enemy[i].x + enemy[i].width, enemy[i].y + enemy[i].height);

			}
			else
			{
				//绘制小敌机
				putimage(enemy[i].x, enemy[i].y, &img_enemy[0][0], NOTSRCERASE);
				putimage(enemy[i].x, enemy[i].y, &img_enemy[0][1], NOTSRCERASE);
			}
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

//生成敌机
void createEnemy() {
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//没有敌机时候，再生成敌机
		if (!enemy[i].live)
		{
			enemy[i].live = true;
			//x,y 是随机的
			//enemy[i].type = rand() % 2;
			enemy[i].x = rand() % (WIDTH-60);
			enemy[i].y = 0;
			break;
		}
	}
}


//敌机移动
void EnemyMove(int speed) {
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy[i].live)
		{
			enemy[i].y += speed;
			if (enemy[i].y > HEIGHT)
			{
				enemy[i].live = false;
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

//子弹打敌机
void playPlance() {
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (!enemy[i].live)
		{
			continue;
		}
		for (int k = 0; k < ENEMY_NUM; k++)
		{
			if (!bull[k].live)
			{
				continue;
			}
			if (bull[k].x > enemy[i].x )
			{
				if (bull[k].x < enemy[i].x + enemy[i].width)
				{
					if (bull[k].y > enemy[i].y)
					{
						if (bull[k].y < enemy[i].y + enemy[i].height)
						{
							bull[i].live = false;
							enemy[i].hp--;
						}
					}
				}
				
			}
		}
		if (enemy[i].live&&enemy[i].hp <= 0)
		{
			enemy[i].live = false;
			printf("%d", i);
		}
	}
}

//定时器 

bool Time(int ms,int id) {
	static DWORD t[10];
	if (clock() - t[id] > ms)
	{
		//创建飞机
		//clock 返回当前毫秒
		t[id] = clock();
		return true;
	}
		return false;
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
		//main方法中 都封装函数
		if (Time(1500,0))
		{
			createEnemy();
		} 
		EnemyMove(1);
		//子弹打敌机
		playPlance();
	}
	return 0;
}