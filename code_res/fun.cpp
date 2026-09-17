#include "fun.h"


void color(int a)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}// 0, 16,  32  ,48  ,64 , 80,   96,  112 ,128 ,144 ,160 , 176    , 192 ,208,  224 ,240
//黑 深蓝 深绿 浅蓝  红  深紫  土黄 浅灰 深灰 亮蓝 亮绿  最淡的蓝 桃红 浅紫  米黄  白  240为白底黑字

//显示速度
int returnspeed()
{
	return 130 - speed;//实际速度30-100，数字越大速度越小，显示速度100-30，数字越大速度越大
}

//关闭界面
void Quit()
{
	closegraph();
	initgraph(Crosswise, Lengthways, EX_SHOWCONSOLE);
	setbkcolor(RGB(150, 190, 230));
	cleardevice();
	settextcolor(BLACK);
	settextstyle(30, 0, _T("宋体"));
	outtextxy(Crosswise / 2 - 200, Lengthways / 2 - 20, _T("欢 迎 下 次 游 玩 ！"));
	Sleep(3000);
	exit(0);
}

//展示菜单
void DisplayMenu()
{
	initgraph(534, 800);
	IMAGE img, start, option, describtion, quit;
	loadimage(&img, _T("snake1.jpg"));  // 加载图片 
	loadimage(&start, _T("开始游戏.jpg"));
	loadimage(&option, _T("游戏设置.jpg"));
	loadimage(&describtion, _T("游戏说明.jpg"));
	loadimage(&quit, _T("退出游戏.jpg"));

	putimage(0, 0, &img);  // 在 (0,0) 位置显示图片
	putimage(150, 200, &start);//图片200*100
	putimage(150, 350, &option);
	putimage(150, 500, &describtion);
	putimage(150, 650, &quit);
}

//打印游戏说明
void GameDescription()
{
	closegraph();
	initgraph(1200, 580, EX_SHOWCONSOLE);

	setbkcolor(RGB(150, 190, 230));
	cleardevice();
	settextcolor(BLACK);
	settextstyle(60, 0, _T("宋体"));
	outtextxy(20, 20, _T("←"));

	settextstyle(25, 0, _T("宋体"));
	outtextxy(100, 65, _T("欢迎游玩贪吃蛇！"));
	settextstyle(20, 0, _T("宋体"));
	outtextxy(100, 100, _T("贪吃蛇游戏说明："));
	outtextxy(100, 125, _T("可在设置中调节地图大小、移动速度、是否有边界墙、切换地图、更改蛇身颜色等"));
	outtextxy(100, 150, _T("进入游戏后，按下 ↑ ↓ ← → 键控制蛇的移动方向"));
	outtextxy(100, 175, _T("死亡后按下R键可再次游玩，按下M键返回主菜单，按下E键退出游戏"));
	outtextxy(100, 200, _T("若您使用的地图不为默认地图，我们强烈建议您不要开启边境墙，这可能会导致食物生成在某些无法进入的地方"));
	MOUSEMSG mou;
	while (1)
	{
		mou = GetMouseMsg();
		if (mou.uMsg == WM_LBUTTONDOWN)
		{
			if (mou.x >= 20 && mou.x <= 80 && mou.y >= 20 && mou.y <= 80)
			{
				closegraph();
				main();
			}
		}
	}
}

//设置界面
void ClickOption()
{
	closegraph();
	initgraph(1200, 580, EX_SHOWCONSOLE);
	setbkcolor(RGB(150, 190, 230));
	cleardevice();
	settextcolor(BLACK);
	settextstyle(60, 0, _T("宋体"));
	outtextxy(20, 20, _T("←"));

	char thecrosswise[10], thelengthways[10], thespeed[10];
	sprintf_s(thecrosswise, "%d", Crosswise);
	sprintf_s(thelengthways, "%d", Lengthways);
	sprintf_s(thespeed, "%d", returnspeed());

	settextstyle(20, 0, _T("宋体"));
	outtextxy(325, 100, _T("-"));
	outtextxy(325, 125, _T("-"));
	outtextxy(325, 150, _T("-"));
	outtextxy(325, 175, _T("-"));
	outtextxy(325, 200, _T("-"));
	outtextxy(325, 225, _T("-"));
	outtextxy(405, 100, _T("+"));
	outtextxy(405, 125, _T("+"));
	outtextxy(405, 150, _T("+"));
	outtextxy(405, 175, _T("+"));
	outtextxy(405, 200, _T("+"));
	outtextxy(405, 225, _T("+"));

	outtextxy(100, 100, _T("地图横向长度"));  outtextxy(350, 100, thecrosswise);
	outtextxy(100, 125, _T("地图纵向长度"));  outtextxy(350, 125, thelengthways);
	outtextxy(100, 150, _T("移动速度"));      outtextxy(350, 150, thespeed);
	outtextxy(100, 175, _T("切换地图"));      outtextxy(350, 175, MAP[maps]);
	outtextxy(100, 200, _T("是否有边界墙"));  outtextxy(350, 200, YN[boder]);
	outtextxy(100, 225, _T("蛇身颜色"));      outtextxy(350, 225, COLOUR[colour]);

	MOUSEMSG mou;
	while (1)
	{
		mou = GetMouseMsg();
		if (mou.uMsg == WM_LBUTTONDOWN)
		{
			if (mou.x >= 20 && mou.x <= 80 && mou.y >= 20 && mou.y <= 80)
			{
				closegraph();
				main();
			}
			if (mou.x >= 323 && mou.x <= 350 && mou.y > 100 && mou.y <= 125 && Crosswise > 520)
			{
				Crosswise -= 20;
				outtextxy(350, 100, _T("    "));
				sprintf_s(thecrosswise, "%d", Crosswise);
				outtextxy(350, 100, thecrosswise);
			}
			if (mou.x >= 323 && mou.x <= 350 && mou.y > 125 && mou.y <= 150 && Lengthways > 300)
			{
				Lengthways -= 10;
				outtextxy(350, 125, _T("    "));
				sprintf_s(thelengthways, "%d", Lengthways);
				outtextxy(350, 125, thelengthways);
			}
			if (mou.x >= 323 && mou.x <= 350 && mou.y > 150 && mou.y <= 175 && speed < 100)
			{
				speed += 5;
				sprintf_s(thespeed, "%d", returnspeed());
				outtextxy(350, 150, thespeed);
			}
			if (mou.x >= 323 && mou.x <= 350 && mou.y > 175 && mou.y <= 200)
			{
				maps--, maps += (maps < 0 ? 5 : 0);
				outtextxy(350, 175, MAP[maps]);
			}
			if (mou.x >= 323 && mou.x <= 350 && mou.y > 200 && mou.y <= 225)
			{
				boder = 1 - boder;
				outtextxy(350, 200, YN[boder]);
			}
			if (mou.x >= 323 && mou.x <= 350 && mou.y > 225 && mou.y <= 250)
			{
				colour--, colour += (colour < 0 ? 14 : 0);
				outtextxy(350, 225, COLOUR[colour]);
			}
			if (mou.x >= 405 && mou.x <= 430 && mou.y > 100 && mou.y <= 125 && Crosswise < 1500)
			{
				Crosswise += 20;
				outtextxy(350, 100, _T("    "));
				sprintf_s(thecrosswise, "%d", Crosswise);
				outtextxy(350, 100, thecrosswise);
			}
			if (mou.x >= 405 && mou.x <= 430 && mou.y > 125 && mou.y <= 150 && Lengthways < 1000)
			{
				Lengthways += 10;
				outtextxy(350, 125, _T("    "));
				sprintf_s(thelengthways, "%d", Lengthways);
				outtextxy(350, 125, thelengthways);
			}
			if (mou.x >= 405 && mou.x <= 430 && mou.y > 150 && mou.y <= 175 && speed > 35)
			{
				speed -= 5;
				sprintf_s(thespeed, "%d", returnspeed());
				outtextxy(350, 150, thespeed);
			}
			if (mou.x >= 405 && mou.x <= 430 && mou.y > 175 && mou.y <= 200)
			{
				maps++, maps -= (maps > 4 ? 5 : 0);
				outtextxy(350, 175, MAP[maps]);
			}
			if (mou.x >= 405 && mou.x <= 430 && mou.y > 200 && mou.y <= 225)
			{
				boder = 1 - boder;
				outtextxy(350, 200, YN[boder]);
			}
			if (mou.x >= 405 && mou.x <= 430 && mou.y > 225 && mou.y <= 250)
			{
				colour++, colour -= (colour > 13 ? 14 : 0);
				outtextxy(350, 225, COLOUR[colour]);
			}
		}
	}

}

//菜单操作
void MenuOperation()
{
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x >= 150 && m.x <= 350 && m.y >= 200 && m.y <= 300)
			{
				Gaming();
				Quit();
			}
			if (m.x >= 150 && m.x <= 350 && m.y >= 350 && m.y <= 450)
			{
				ClickOption();
			}
			if (m.x >= 150 && m.x <= 350 && m.y >= 500 && m.y <= 600)
			{
				GameDescription();
			}
			if (m.x >= 150 && m.x <= 350 && m.y >= 650 && m.y <= 750)
			{ 
				Quit();
			}
		}
	}
}



//游戏的运行
void Gaming()
{
	closegraph();
	initgraph(Crosswise, Lengthways, EX_SHOWCONSOLE);
	srand(time(nullptr));//随机数种子
	GameScene scene;
	settextstyle(15, 0, _T("宋体"));
	while (!scene.Exit())
	{
		scene.run();
		Sleep(speed);
		scene.changestep();
		scene.changetime(speed);
	}
	closegraph();
}

