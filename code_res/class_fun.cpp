#include "fun.h"


int Crosswise = 640, Lengthways = 480, speed = 70, colour = 0,maps = 0;
bool boder = 1;
char YN[2][7] = { "否","是" };
COLORREF colors[14] = {BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE};
char COLOUR[14][7] = { "蓝色", "绿色", "青色", "红色", "紫色", "棕色", "浅灰", "亮蓝", "亮绿", "亮青", "亮红", "亮紫", "黄色", "白色" };
char MAP[5][10] = { "地图一", "地图二", "地图三", "地图四", "地图五"};

//节点绘制
void Sprite::draw()
{
	{

		setfillcolor(m_color);
		fillrectangle(m_x, m_y, m_x + 10, m_y + 10);//显示框大小（填充颜色）
	}
}
//节点移动函数
void Sprite::moveBy(int dx, int dy)
{
	m_x += dx;
	m_y += dy;
}
//节点碰撞判定
bool Sprite::collision(const Sprite& other)
{
	return m_x == other.m_x && m_y == other.m_y;
}

//墙的构造函数
Wall::Wall() :Sprite()
{
	switch (maps)
	{
	case 1://十字
		for (int i = 0; i < Crosswise / 10; i++)
		{
			walls.push_back(Sprite(i * 10, Lengthways / 2, DARKGRAY));
		}
		for (int i = 0; i < Lengthways / 10; i++)
		{
			walls.push_back(Sprite(Crosswise / 2, i * 10, DARKGRAY));
		}
		break;
	case 2://坤卦
		for (int i = 0; i < Crosswise / 10; i++)
		{
			walls.push_back(Sprite(i * 10, Lengthways / 3, DARKGRAY));
			walls.push_back(Sprite(i * 10, 2 * Lengthways / 3, DARKGRAY));
			if (i == Crosswise / 30) i = 2 * Crosswise / 30;
		}
		break;
	case 3://六宫格
		for(int i = 0; i < Lengthways / 10; i++) walls.push_back(Sprite(Crosswise / 2,i * 10, DARKGRAY));
		for (int i = 0; i < Crosswise / 10; i++)
		{
			walls.push_back(Sprite(i * 10, Lengthways / 3, DARKGRAY));
			if (i == Crosswise / 60) i = Crosswise / 30;
		}
		for (int i = 0; i < Crosswise / 10; i++)
		{
			walls.push_back(Sprite(i * 10, 2 * Lengthways / 3, DARKGRAY));
			if (i == 2 * Crosswise / 30) i = 5 * Crosswise / 60;
		}
		break;
	case 4:
		for (int i = 0; i < Crosswise / 10; i+=8)
		{
			for (int j = 8; j < Lengthways / 10; j+=8)
			{
				walls.push_back(Sprite(i * 10, j * 10, DARKGRAY));
			}
		}
		break;
	}
}
//墙的绘制函数
void Wall::draw()
{
	for (int i = 0; i < walls.size(); i++)
	{
		walls[i].draw();
	}
}
//获取墙块数量
size_t Wall::getsize()
{
	return walls.size();
}


//蛇的构造函数
Snake::Snake(int x, int y) : Sprite(x, y), dir(VK_RIGHT)
{
	//初始化一条蛇
	nodes.push_back(Sprite(20, 0));
	nodes.push_back(Sprite(10, 0));
	nodes.push_back(Sprite(0, 0));
}
//蛇的绘制函数
void Snake::draw()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		nodes[i].draw();
	}
}
//蛇 游戏结束
void Snake::gameOver(GameScene& scene) 
{
	cleardevice();
	settextcolor(RED);
	settextstyle(20, 0, _T("宋体"));
	char msg[300];
	sprintf_s(msg, sizeof(msg), "Game Over! Score: %d Step: %d Time: %lf", nodes.size() * 10 - 30, step, Time);
	outtextxy(Crosswise / 2 - 200, Lengthways / 2 - 20, msg);
	outtextxy(Crosswise / 2 - 210, Lengthways / 2 + 20, _T("Press 'R' to Retry,'E' to Exit or 'M' to main menu"));
	settextcolor(WHITE);
	settextstyle(15, 0, _T("宋体"));
	EndBatchDraw();
	scene.setGameOverFlag(true);  // 设置游戏结束标志
}
//蛇 身体移动 死亡判定 有边界
void Snake::bodyMove(GameScene& scene) 
{
	for (size_t i = nodes.size() - 1; i > 0; --i) {
		nodes[i] = nodes[i - 1];
	}
	switch (dir) {
	case VK_UP:    nodes[0].moveBy(0, -10); break;
	case VK_DOWN:  nodes[0].moveBy(0, 10);  break;
	case VK_LEFT:  nodes[0].moveBy(-10, 0); break;
	case VK_RIGHT: nodes[0].moveBy(10, 0);  break;
	}
	for (size_t i = 1; i < nodes.size(); i++) {
		if (nodes[0].collision(nodes[i])) {
			gameOver(scene);
			return;
		}
	}
	if (getHeadX() < 0 || getHeadX() >= Crosswise || getHeadY() < 0 || getHeadY() >= Lengthways) {
		if (boder)
		{
			gameOver(scene);
			return;
		}
		else
		{
			if (getHeadX() < 0) nodes[0].moveBy(Crosswise,0);
			if (getHeadX() >= Crosswise) nodes[0].moveBy(-Crosswise,0);
			if (getHeadY() < 0) nodes[0].moveBy(0, Lengthways);
			if (getHeadY() >= Lengthways) nodes[0].moveBy(0, -Lengthways);
		}
	}
}

//食物随机位置函数
void Food::changePos() {
	// 定义积分器所在区域的范围
	const int scoreAreaX1 = 0;
	const int scoreAreaY1 = 0;
	const int scoreAreaX2 = 250;
	const int scoreAreaY2 = 30;

	// 确保食物不会刷新在积分器所在的区域
	do {
		m_x = rand() % (Crosswise / 10) * 10;
		m_y = rand() % (Lengthways / 10) * 10;
	} while (m_x >= scoreAreaX1 && m_x <= scoreAreaX2 && m_y >= scoreAreaY1 && m_y <= scoreAreaY2);
}
//食物绘制
void Food::draw()
{
	setfillcolor(m_color);
	solidellipse(m_x, m_y, m_x + 10, m_y + 10);
}

//获取键盘信息
void GameScene::onMsg(const ExMessage& msg)
{
	if (msg.message == WM_KEYDOWN)//判断是否按下键盘
	{
		switch (msg.vkcode)
		{
		case VK_UP:
			if (snake.dir != VK_DOWN)
			{
				snake.dir = msg.vkcode;
			}
			break;
		case VK_DOWN:
			if (snake.dir != VK_UP)
			{
				snake.dir = msg.vkcode;
			}
			break;
		case VK_LEFT:
			if (snake.dir != VK_RIGHT)
			{
				snake.dir = msg.vkcode;
			}
			break;
		case VK_RIGHT:
			if (snake.dir != VK_LEFT)
			{
				snake.dir = msg.vkcode;
			}
			break;
		case 'R':
		case 'r':
			if (gameOverFlag) {
				snake = Snake();
				food = Food();
				score = 0;
				snake.Time = 0;
				gameOverFlag = false;
			}
			break;
		/**/case 'E':
		case 'e':
			if (gameOverFlag) {
				gameOverFlag = false;
				exit = true;
				Quit();
			}
			break;
		case 'M':
		case 'm':
			if (gameOverFlag) {
				gameOverFlag = false;
				exit = true;
				main();
			}
			break;
		}
	
	}
}
//蛇吃食物
void GameScene::SnakeEatFood()
{
	if (snake.collision(food))
	{
		snake.incrment();
		food.changePos();
		score += 10; // 每吃一个食物加 10 分
	}
}
//蛇撞墙
void GameScene::SnakeCollideWall()
{
	for (int i = 0; i < wall.getsize(); i++) 
		if (snake.collision(wall.walls[i]))
		{
			snake.gameOver(*this);
			return;
		}
}
//监听,游戏结束后的选项
void GameScene::listenForRestartOrExit()
{
	ExMessage msg;
	while (peekmessage(&msg, EM_KEY)) {
		onMsg(msg); // 改动位置 7: 处理按键事件
	}
}
//场景运行函数
void GameScene::run()
{
	if (!gameOverFlag)
	{
		BeginBatchDraw();//双缓冲绘图
		//setbkcolor(RGB(144, 238, 144));//浅绿色背景
		cleardevice();//清屏
		for (int i = 0; i < wall.getsize(); i++) if (food.collision(wall.walls[i])) food.changePos();//如果食物生成在墙里则刷新位置
		snake.draw();
		food.draw();
		wall.draw();
		char scoreStr[80];
		sprintf_s(scoreStr, "Score: %d Step: %d Time: %lf", score, snake.step, snake.Time);
		outtextxy(10, 10, scoreStr);
		EndBatchDraw();
		snake.bodyMove(*this);//蛇的移动
		SnakeCollideWall();
		SnakeEatFood();
		ExMessage msg = { 0 };
		while (peekmessage(&msg, EX_KEY))
		{
			onMsg(msg);
		}
	}
	else {
		listenForRestartOrExit();
	}
}
