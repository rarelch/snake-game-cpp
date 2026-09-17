#define _CRT_SECURE_NO_WARNINGS 
#ifndef CLASS
#define CLASS
//#include <bits/stdc++.h>
#include <easyx.h>
#include <iostream>
#include <graphics.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <windows.h>
#include <conio.h>
using namespace  std;

extern int Lengthways, Crosswise, speed, colour, maps;//长，宽，高，速度，颜色，地图
extern bool boder;//是否有边界墙
extern char YN[2][7], COLOUR[14][7], MAP[5][10];//打印相关信息
extern COLORREF colors[14];//颜色库

class Sprite//节点
{
public:
	Sprite() : Sprite(0, 0,(colors[colour])) {};
	Sprite(int x, int y, COLORREF C) :m_x(x), m_y(y), m_color(C) {};
	Sprite(int x, int y) :m_x(x), m_y(y), m_color(colors[colour]) {};
	virtual void draw();//设置填充颜色
	void moveBy(int dx, int dy);//节点移动函数
	bool collision(const Sprite& other);//节点碰撞判定
	int getX() const { return m_x; } // 获取 x 坐标
	int getY() const { return m_y; } // 获取 y 坐标
protected:
	int m_x;
	int m_y;
	COLORREF m_color;//颜色
};

class Wall :public Sprite//墙类
{
public:
	Wall();
	void draw() override;
	size_t getsize();//获取墙块数量
	vector<Sprite> walls;//类似于蛇，将墙看作多个墙块的集合
};

class GameScene;//声明场景类

class Snake : public Sprite//蛇类
{
public:
	int getHeadX() const { return nodes[0].getX(); }
	int getHeadY() const { return nodes[0].getY(); }//获取蛇头位置
	Snake() :Snake(0, 0) {}
	Snake(int x, int y);//蛇的构造函数
	void draw() override;//蛇的绘制函数
	void bodyMove(GameScene& scene);//蛇 身体移动 死亡判定
	void gameOver(GameScene& scene);
	bool collision(const Sprite& other) { return nodes[0].collision(other); }//蛇的碰撞判定，改为了蛇头碰撞
	void incrment() { nodes.push_back(Sprite()); }//蛇的节数增加
public:
	//蛇的身体
	vector<Sprite> nodes;//蛇的节点
	int dir;//方向
	int step = 0;
	double Time = 0;
	bool gameOverFlag = false;
};

class Food:public Sprite//食物类
{
public:
	void changePos();//食物随机位置函数
	Food() :Sprite(0, 0){ changePos(); }//构造函数，随机生成
	void draw()override;//食物绘制
};

class GameScene
{
public:
	GameScene() {}
	void run();//场景运行函数
	void onMsg(const ExMessage& msg);//获取键盘信息
	void SnakeEatFood();//蛇吃食物
	void SnakeCollideWall();//蛇撞墙
	void listenForRestartOrExit();//游戏结束后的键盘消息接收
	void setGameOverFlag(bool flag) { gameOverFlag = flag; }
	void changestep() { snake.step++; }//改变步数
	void changetime(int T) { snake.Time += T / 1000.0; }//改变时间
	bool Exit() { return exit; }
	
private:
	Snake snake;
	Food food;
	Wall wall;
	int score = 0;
	bool gameOverFlag = false;
	bool exit = false;
};



















#endif
