#include<time.h>
#include<Windows.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include"function.h"

#define HIGH 864
#define WIDTH 1536
#define SIZE 50
#define BRICKMAX 80
#define BOXMAX 10

int viewchoice = 1;//1代表初始界面，2代表关卡选择界面，3代表游戏界面
int gamechoice;//记录关卡值
int high;//每关y方向最多有多少块砖
int width;//每关x方向最多有多少块砖
int size;//用于记录每关的尺寸
int brickposition[2][BRICKMAX] = { 0 };//记录砖块位置
int boxposition[2][BOXMAX] = { 0 };//记录箱子位置
int aimposition[2][BOXMAX] = { 0 };//记录箱子的目标位置
int position_x, position_y;//记录人所在位置
int distance = 0;
int movetype = { 0 }, movechoice = 0;
int redotimes = 5;
int levelsteps[2][10] = { 0 };//记录每关是否通过和步数
SYSTEMTIME time1;

void Startup()
{
	GetLocalTime(&time1);
	initgraph(WIDTH, HIGH);
	BeginBatchDraw();
	Welcome();
}
void Welcome()
{
	//设置屏幕大小为WIDTH*1280，为16：9的长宽比
	setbkcolor(BLACK);								//设置背景颜色为黑色
	cleardevice();									//清屏

	Printtext1();									//打出信息并停留1秒
	Sleep(2000);

	for (int colorchange = 255; colorchange >= 0; colorchange--)
	{
		settextcolor(RGB(colorchange, colorchange, colorchange));
		Printtext1();								//字体颜色渐变
		Sleep(10);
	}

	cleardevice();									//清屏

	Printtext2();
	Sleep(2000);

	for (int colorchange = 0; colorchange <= 255; colorchange++)
	{
		setbkcolor(RGB(colorchange, colorchange, colorchange));
		cleardevice();
		Printtext2();								//背景颜色渐变
		Sleep(12);
	}
}
void Printtext1()
{
	LOGFONT f;									// 该结构体调整字体属性。本处列出了所有用得到的属性，平常修改时只修改变化量
	gettextstyle(&f);							// 获取当前字体设置
	f.lfEscapement = 0;							// 设置字符串依次上抬角度为0
	f.lfOrientation = 0;						// 设置每个字符逆时针旋转角度为0
	f.lfWeight = 300;							// 设置笔画粗细为LIGHT
	f.lfItalic = 0;								// 设置为非斜体
	f.lfUnderline = 1;							// 设置为带下划线
	f.lfStrikeOut = 0;							// 设置为不带删除线
	f.lfQuality = PROOF_QUALITY;				// 设置文字的输出质量为正稿质量
	settextstyle(&f);							// 保存字体设置
	settextstyle(72, 0, _T("方正粗黑宋简体"));	// 设置字体高度为 42，字体平均宽度为自适应，字体为方正粗黑宋简体

	RECT r = { 0, 50, WIDTH, HIGH };
	drawtext(_T("制作人员"), &r, DT_CENTER);		//居中显示
	r = { 0, 310, WIDTH, HIGH };
	drawtext(_T("学       号"), &r, DT_CENTER);
	r = { 0, 570, WIDTH, HIGH };
	drawtext(_T("指导教师"), &r, DT_CENTER);

	f.lfUnderline = 0;							// 设置为不带下划线
	settextstyle(&f);							// 保存字体设置
	settextstyle(72, 0, _T("方正粗黑宋简体"));

	r = { 0, 170, WIDTH, HIGH };
	drawtext(_T("马光远       方尧    "), &r, DT_CENTER);
	r = { 0, 430, WIDTH, HIGH };
	drawtext(_T("180610112    190410102"), &r, DT_CENTER);
	r = { 0, 690, WIDTH, HIGH };
	drawtext(_T("吴晓军    乔长浩"), &r, DT_CENTER);

	FlushBatchDraw();
}
void Printtext2()
{
	settextcolor(WHITE);

	LOGFONT f;									// 该结构体调整字体属性。本处列出了所有用得到的属性，平常修改时只修改变化量
	gettextstyle(&f);							// 获取当前字体设置
	f.lfEscapement = 0;							// 设置字符串依次上抬角度为0
	f.lfOrientation = 0;						// 设置每个字符逆时针旋转角度为0
	f.lfWeight = 300;							// 设置笔画粗细为LIGHT
	f.lfItalic = 0;								// 设置为非斜体
	f.lfUnderline = 0;							// 设置为不带下划线
	f.lfStrikeOut = 0;							// 设置为不带删除线
	f.lfQuality = PROOF_QUALITY;				// 设置文字的输出质量为正稿质量
	settextstyle(&f);							// 保存字体设置
	settextstyle(120, 0, _T("方正粗黑宋简体"));	// 设置字体高度为 120，字体平均宽度为自适应，字体为方正粗黑宋简体

	RECT r = { 0, 120, WIDTH, HIGH };
	drawtext(_T("高级语言程序设计"), &r, DT_CENTER);		//居中显示
	r = { 0, 300, WIDTH, HIGH };
	drawtext(_T("课程设计"), &r, DT_CENTER);

	f.lfUnderline = 1;							// 设置为带下划线
	settextstyle(&f);							// 保存字体设置
	settextstyle(108, 0, _T("方正粗黑宋简体"));

	r = { 0, 570, WIDTH, HIGH };
	drawtext(_T("推箱子"), &r, DT_CENTER);

	f.lfUnderline = 0;							// 设置为不带下划线
	settextstyle(&f);							// 保存字体设置

	FlushBatchDraw();
}
void Show()
{
	if (viewchoice == 1)
	{
		View1();
	}
	if (viewchoice == 2)
	{
		View2();
	}
	if (viewchoice == 3)
	{
		View3();
	}
}
void View1()
{
	int i, j;
	IMAGE img_backgroundbrick, img_box;
	loadimage(&img_backgroundbrick, "C:\\推箱子素材\\backgroundbrick.jpg");
	loadimage(&img_box, "C:\\推箱子素材\\box.jpg", 2.5 * SIZE, 2.5 * SIZE);

	//铺地板背景图 
	for (i = 1; i <= WIDTH / SIZE + 1; i++)
	{
		for (j = 1; j <= HIGH / 2 / SIZE + 1; j++)
		{
			putimage((i - 1) * SIZE, (j - 1) * 2 * SIZE, &img_backgroundbrick);
		}
	}

	//绘制上方“推箱子”、下方“开始”
	setbkmode(TRANSPARENT);
	settextstyle(150, 0, _T("方正粗黑宋简体"));
	RECT r = { 0, 100, WIDTH, HIGH };
	drawtext(_T("推箱子"), &r, DT_CENTER);
	r = { 0, 500, WIDTH, HIGH };
	drawtext(_T("开始"), &r, DT_CENTER);
	//rectangle(WIDTH / 2 - 140, 520, WIDTH / 2 + 120, 620);

	//绘制中央箱子图形
	putimage(WIDTH / 2 - 2.5 * SIZE / 2, 300, &img_box);
	FlushBatchDraw();
}
void View2()
{
	int i, j, k;
	IMAGE  img_esc1, img_esc2, img_guanqia1, img_guanqia2, img_backgroundbrick;
	loadimage(&img_backgroundbrick, "C:\\推箱子素材\\backgroundbrick.jpg");
	loadimage(&img_esc1, "C:\\推箱子素材\\esc_1.jpg");
	loadimage(&img_esc2, "C:\\推箱子素材\\esc_2.jpg");
	loadimage(&img_guanqia1, "C:\\推箱子素材\\guanqia_1.jpg");
	loadimage(&img_guanqia2, "C:\\推箱子素材\\guanqia_2.jpg");
	//铺地板背景图 
	for (i = 1; i <= WIDTH / SIZE + 1; i++)
	{
		for (j = 1; j <= HIGH / 2 / SIZE + 1; j++)
		{
			putimage((i - 1) * SIZE, (j - 1) * 2 * SIZE, &img_backgroundbrick);
		}
	}

	//绘制关卡图形
	for (i = 1; i <= 3; i++)
	{
		for (j = 1; j <= 3; j++)
		{
			putimage(i / 4.0 * WIDTH - SIZE, 200 + (j - 1) * 140, &img_guanqia2, NOTSRCERASE);
			putimage(i / 4.0 * WIDTH - SIZE, 200 + (j - 1) * 140, &img_guanqia1, SRCINVERT);
		}
	}
	putimage(1 / 4.0 * WIDTH - SIZE, 200 + (j - 1) * 140, &img_guanqia2, NOTSRCERASE);
	putimage(1 / 4.0 * WIDTH - SIZE, 200 + (j - 1) * 140, &img_guanqia1, SRCINVERT);

	//绘制返回图形
	putimage(110, 40, &img_esc2, NOTSRCERASE);
	putimage(110, 40, &img_esc1, SRCINVERT);
	//rectangle(10, 20, 10 + 88, 20 + 88 + 30);

	//绘制关卡数字
	setcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(80, 0, _T("方正粗黑宋简体"));
	char str[10];
	k = 1;
	for (j = 1; j <= 3; j++)
	{
		for (i = 1; i <= 3; i++)
		{
			_itoa_s(k, str, 10);
			outtextxy(i / 4.0 * WIDTH - SIZE + 20, 200 + (j - 1) * 140, str);
			k++;
		}
	}
	_itoa_s(k, str, 10);
	outtextxy(1 / 4.0 * WIDTH - SIZE + 10, 210 + 3 * 140, str);

	//绘制正上方“关卡选择”标题
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(100, 0, _T("方正粗黑宋简体"));
	RECT r = { 0, 50, WIDTH, HIGH };
	drawtext(_T("关卡选择"), &r, DT_CENTER);
	//outtextxy(180, 30, "关卡选择");

	//绘制左上方“返回”
	settextstyle(60, 0, _T("方正粗黑宋简体"));
	outtextxy(100, 100, "返回");
	FlushBatchDraw();
}
void View3()
{
	int i, j;
	IMAGE img_backgroundbrick, img_brick, img_box, img_man1, img_man2, img_successbox, img_aim1, img_aim2, img_up, img_down, img_left, img_right, img_menu1, img_menu2;
	loadimage(&img_backgroundbrick, "C:\\推箱子素材\\backgroundbrick.jpg", size / 2, size);
	loadimage(&img_man1, "C:\\推箱子素材\\man_1.jpg", size, size);
	loadimage(&img_man2, "C:\\推箱子素材\\man_2.jpg", size, size);
	loadimage(&img_menu1, "C:\\推箱子素材\\menu_1.jpg", 3 * SIZE, 3 * SIZE * 128 / 268);
	loadimage(&img_menu2, "C:\\推箱子素材\\menu_2.jpg", 3 * SIZE, 3 * SIZE * 128 / 268);
	loadimage(&img_brick, "C:\\推箱子素材\\brick.jpg", size, size);
	loadimage(&img_aim1, "C:\\推箱子素材\\aim_1.jpg", size, size);
	loadimage(&img_aim2, "C:\\推箱子素材\\aim_2.jpg", size, size);
	loadimage(&img_box, "C:\\推箱子素材\\box.jpg", size, size);
	loadimage(&img_successbox, "C:\\推箱子素材\\successbox.jpg", size, size);
	loadimage(&img_up, "C:\\推箱子素材\\up.jpg", size, size);
	loadimage(&img_down, "C:\\推箱子素材\\down.jpg", size, size);
	loadimage(&img_left, "C:\\推箱子素材\\left.jpg", size, size);
	loadimage(&img_right, "C:\\推箱子素材\\right.jpg", size, size);
	//绘制地板背景图
	cleardevice();
	for (i = 1; i <= WIDTH / (size / 2) + 1; i++)
	{
		for (j = 1; j <= HIGH / size + 1; j++)
		{
			putimage((i - 1) * size / 2, (j - 1) * size, &img_backgroundbrick);
		}
	}
	//绘制菜单显示标识
	putimage(850, 50, &img_menu2, NOTSRCERASE);
	putimage(850, 50, &img_menu1, SRCINVERT);
	putimage(850, 150, &img_menu2, NOTSRCERASE);
	putimage(850, 150, &img_menu1, SRCINVERT);
	putimage(850, 250, &img_menu2, NOTSRCERASE);
	putimage(850, 250, &img_menu1, SRCINVERT);
	putimage(850, 350, &img_menu2, NOTSRCERASE);
	putimage(850, 350, &img_menu1, SRCINVERT);
	putimage(850, 450, &img_menu2, NOTSRCERASE);
	putimage(850, 450, &img_menu1, SRCINVERT);
	putimage(850, 550, &img_menu2, NOTSRCERASE);
	putimage(850, 550, &img_menu1, SRCINVERT);

	char str[10];
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, _T("方正粗黑宋简体"));
	_itoa_s(gamechoice, str, 10);
	outtextxy(890, 50, "关卡");
	outtextxy(905, 85, str);
	_itoa_s(distance, str, 10);
	outtextxy(890, 150, "步数");
	outtextxy(905, 185, str);
	outtextxy(860, 250, "撤销次数");
	_itoa_s(redotimes, str, 10);
	outtextxy(910, 285, str);
	settextstyle(60, 0, _T("方正粗黑宋简体"));
	outtextxy(850, 355, "主界面");
	outtextxy(870, 450, "重置");
	outtextxy(870, 550, "撤销");
	setcolor(YELLOW);
	settextstyle(40, 0, _T("方正粗黑宋简体"));
	outtextxy(1050, 50, "操作说明：");
	outtextxy(1050, 110, "上:键盘W/w/上 鼠标点击上标");
	outtextxy(1050, 170, "下:键盘S/s/上 鼠标点击下标");
	outtextxy(1050, 230, "上:键盘A/a/上 鼠标点击左标");
	outtextxy(1050, 290, "下:键盘D/d/上 鼠标点击右标");
	outtextxy(1050, 350, "每局可撤销次数为5");
	outtextxy(1050, 410, "退出游戏：Ctrl+w");

	//绘制box
	for (i = 0; boxposition[0][i] > 0; i++)
	{
		putimage((boxposition[0][i]) * size, (boxposition[1][i]) * size, &img_box);
	}
	//绘制砖块
	for (i = 0; brickposition[0][i] > 0; i++)
	{
		putimage((brickposition[0][i]) * size, (brickposition[1][i]) * size, &img_brick);
	}
	//绘制aim块
	for (i = 0; aimposition[0][i] > 0; i++)
	{
		putimage((aimposition[0][i]) * size, (aimposition[1][i]) * size, &img_aim2, NOTSRCERASE);
		putimage((aimposition[0][i]) * size, (aimposition[1][i]) * size, &img_aim1, SRCINVERT);
	}
	//绘制成功的块
	for (i = 0; aimposition[0][i] > 0; i++)
	{
		for (j = 0; boxposition[0][j] > 0; j++)
		{
			if (aimposition[0][i] == boxposition[0][j] && aimposition[1][i] == boxposition[1][j])
			{
				putimage((aimposition[0][i]) * size, (aimposition[1][i]) * size, &img_successbox);
			}
		}
	}
	//绘制人
	putimage((position_x) * size, (position_y) * size, &img_man2, NOTSRCERASE);
	putimage((position_x) * size, (position_y) * size, &img_man1, SRCINVERT);
	//绘制上下左右标识
	putimage((WIDTH / size - 3) * size, (HIGH / size - 3.5) * size, &img_up);
	putimage((WIDTH / size - 3) * size, (HIGH / size - 2) * size, &img_down);
	putimage((WIDTH / size - 4.5) * size, (HIGH / size - 2) * size, &img_left);
	putimage((WIDTH / size - 1.5) * size, (HIGH / size - 2) * size, &img_right);
	FlushBatchDraw();
}
void Mapreset()//初始化砖块，箱子，人，箱子目标位置
{
	int i, j;

	//重置brickposition
	for (i = 0; i < BRICKMAX; i++)
	{
		brickposition[0][i] = 0;
		brickposition[1][i] = 0;
	}
	//重置boxposition,aimposition
	for (i = 0; i < BOXMAX; i++)
	{
		boxposition[0][i] = 0;
		boxposition[1][i] = 0;
		aimposition[0][i] = 0;
		aimposition[1][i] = 0;
	}
	distance = 0;
	movechoice = 0;
	movetype = 0;
	redotimes = 5;
	//重置brickposition，boxposition，aimposition,position_x,position_y，size
	//第一关
	if (gamechoice == 1)
	{
		int brickposition1[2][28] = { {3,4,5,5,5,6,7,8,8,8,7,6,6,6,6,5,4,4,4,3,2,1,1,1,2,3,3,3}, {1,1,1,2,3,3,3,3,4,5,5,5,6,7,8,8,8,7,6,6,6,6,5,4,4,4,3,2} };
		for (i = 0; i < 28; i++)
		{
			brickposition[0][i] = brickposition1[0][i];
			brickposition[1][i] = brickposition1[1][i];
		}
		int boxposition1[2][4] = { { 4,6,4,5 }, { 4,4,5,6 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 3; j++)
			{
				boxposition[i][j] = boxposition1[i][j];			//载入第一关箱子初始位置
			}
		}

		int aimposition1[2][4] = { { 4,7,2,5 }, { 2,4,5,7 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 3; j++)
			{
				aimposition[i][j] = aimposition1[i][j];			//载入第一关箱子目标位置
			}
		}
		position_x = 5; position_y = 5;

		width = 8; 
		high = 8;
		size = min(HIGH / (high + 2), HIGH / (width + 2));
		if (size % 2 == 0)
		{
			size = size;
		}
		else
		{
			size = size - 1;
		}
	}
	if (gamechoice == 2)	//第二关
	{
		int brickposition2[2][39] = { { 1,2,3,4,5,5,5,5,5,6,7,7,7,8,9,9,9,9,9,9,8,7,6,6,6,5,4,3,2,2,2,2,3,3,2,1,1,1,1 }, { 1,1,1,1,1,2,3,4,5,5,5,4,3,3,3,4,5,6,7,8,8,8,8,7,9,9,9,9,9,8,7,6,6,5,5,5,4,3,2 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 38; j++)
			{
				brickposition[i][j] = brickposition2[i][j];
			}
		}

		int boxposition2[2][3] = { { 3,4,3 }, { 3,3,4 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 2; j++)
			{
				boxposition[i][j] = boxposition2[i][j];			//载入第二关箱子初始位置
			}
		}

		int aimposition2[2][3] = { { 8,8,8 }, { 4,5,6 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 2; j++)
			{
				aimposition[i][j] = aimposition2[i][j];			//载入第二关箱子目标位置
			}
		}
		position_x = 2; position_y = 2;

		width = 9; 
		high = 9;
		size = min(HIGH / (high + 2), HIGH / (width + 2));
		if (size % 2 == 0)
		{
			size = size;
		}
		else
		{
			size = size - 1;
		}
	}
	if (gamechoice == 3)	//第三关
	{
		int brickposition3[2][35] = { { 2,3,4,5,6,7,8,8,9,10,10,10,10,9,9,9,8,7,6,5,5,5,4,3,2,2,1,1,1,1,2,2,4,5,6 }, { 1,1,1,1,1,1,1,2,2,2,3,4,5,5,6,7,7,7,7,7,6,5,7,7,7,6,6,5,4,3,3,2,3,3,3 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 34; j++)
			{
				brickposition[i][j] = brickposition3[i][j];
			}
		}

		int boxposition3[2][4] = { { 3,5,8,7 }, { 3,4,4,5 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 3; j++)
			{
				boxposition[i][j] = boxposition3[i][j];			//载入第三关箱子初始位置
			}
		}

		int aimposition3[2][4] = { { 3,4,3,4 }, { 5,5,6,6 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 3; j++)
			{
				aimposition[i][j] = aimposition3[i][j];			//载入第三关箱子目标位置
			}
		}
		position_x = 3; position_y = 4;
		
		width = 10; 
		high = 7;
		size = min(HIGH / (high + 2), HIGH / (width + 2));
		if (size % 2 == 0)
		{
			size = size;
		}
		else
		{
			size = size - 1;
		}
	}
	if (gamechoice == 4)	//第四关
	{
		int brickposition4[2][26] = { { 2,3,4,5,5,5,5,6,6,6,6,6,5,4,3,2,1,1,1,1,2,2,1,1,1,2 }, { 1,1,1,1,2,3,4,4,5,6,7,8,8,8,8,8,8,7,6,5,5,4,4,3,2,2 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 25; j++)
			{
				brickposition[i][j] = brickposition4[i][j];
			}
		}

		int boxposition4[2][5] = { { 3,3,4,3,4 }, { 3,4,5,6,7 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 4; j++)
			{
				boxposition[i][j] = boxposition4[i][j];			//载入第四关箱子初始位置
			}
		}

		int aimposition4[2][5] = { { 2,2,3,4,5 }, { 6,7,7,7,7 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 4; j++)
			{
				aimposition[i][j] = aimposition4[i][j];			//载入第四关箱子目标位置
			}
		}
		position_x = 2; position_y = 3;

		width = 6;
		high = 8;
		size = min(HIGH / (high + 2), HIGH / (width + 2));
		if (size % 2 == 0)
		{
			size = size;
		}
		else
		{
			size = size - 1;
		}
	}
	if (gamechoice == 5)	//第五关 从本关开始先行后列
	{
		int brickposition5[2][34] = { { 2,3,4,5,6,5,6,7,7,7,8,8,8,8,8,7,6,5,4,3,2,1,1,1,1,1,2,2,2,3,3,5,5,6 }, { 1,1,1,1,1,2,2,2,3,4,4,5,6,7,8,8,8,8,8,8,8,8,7,6,5,4,4,3,2,4,5,4,5,6 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 33; j++)
			{
				brickposition[i][j] = brickposition5[i][j];
			}
		}

		int boxposition5[2][3] = { { 4,3,6 }, { 3,6,7 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 2; j++)
			{
				boxposition[i][j] = boxposition5[i][j];			//载入第五关箱子初始位置
			}
		}

		int aimposition5[2][3] = { { 2,2,2 }, { 5,6,7 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 2; j++)
			{
				aimposition[i][j] = aimposition5[i][j];			//载入第五关箱子目标位置
			}
		}
		position_x = 3; position_y = 2;

		width = 8;
		high = 8;
		size = min(HIGH / (high + 2), HIGH / (width + 2));
		if (size % 2 == 0)
		{
			size = size;
		}
		else
		{
			size = size - 1;
		}
	}
	if (gamechoice == 6)	//第六关
	{
		int brickposition6[2][62] = { { 1,2,3,4,4,5,6,7,8,9,10,10,10,10,11,11,11,11,11,12,13,13,13,13,12,11,10,9,9,8,8,7,6,5,4,3,2,2,2,2,1,1,1,1,1,1,6,7,8,9,9,9,6,5,4,3,3,3,5,8,7,4 }, { 2,2,2,2,1,1,1,1,1,1,1,2,3,4,4,5,6,7,8,8,8,9,10,11,11,11,11,11,10,10,11,11,11,11,11,11,11,10,9,8,8,7,6,5,4,3,3,3,3,6,7,8,9,9,9,6,5,4,4,5,8,7 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 60; j++)
			{
				brickposition[i][j] = brickposition6[i][j];
			}
		}

		int boxposition6[2][5] = { { 5,7,6,5,7 }, { 5,5,6,7,7 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 4; j++)
			{
				boxposition[i][j] = boxposition6[i][j];			//载入第六关箱子初始位置
			}
		}

		int aimposition6[2][5] = { { 5,9,6,3,7 }, { 3,5,6,7,9 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 4; j++)
			{
				aimposition[i][j] = aimposition6[i][j];			//载入第六关箱子目标位置
			}
		}
		position_x = 12; position_y = 9;

		width = 13;
		high = 11;
		size = min(HIGH / (high + 2), HIGH / (width + 2));
		if (size % 2 == 0)
		{
			size = size;
		}
		else
		{
			size = size - 1;
		}
	}
	if (gamechoice == 7)	//第七关
	{
		int brickposition7[2][37] = { { 4,5,6,7,8,9,10,10,10,10,10,10,9,9,9,8,7,6,5,4,3,2,1,1,1,2,3,3,3,3,3,4,7,7,7,7,6 }, { 1,1,1,1,1,1,1,2,3,4,5,6,6,7,8,8,8,8,8,8,8,8,8,7,6,6,6,5,4,3,2,2,2,3,5,6,5 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 36; j++)
			{
				brickposition[i][j] = brickposition7[i][j];
			}
		}

		int boxposition7[2][5] = { { 4,6,8,5,5 }, { 4,4,4,5,6 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 4; j++)
			{
				boxposition[i][j] = boxposition7[i][j];			//载入第七关箱子初始位置
			}
		}

		int aimposition7[2][5] = { { 2,3,4,5,6 }, { 7,7,7,7,7 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 4; j++)
			{
				aimposition[i][j] = aimposition7[i][j];			//载入第七关箱子目标位置
			}
		}
		position_x = 9; position_y = 2;

		width = 10;
		high = 8;
		size = min(HIGH / (high + 2), HIGH / (width + 2));
		if (size % 2 == 0)
		{
			size = size;
		}
		else
		{
			size = size - 1;
		}
	}
	if (gamechoice == 8)	//第八关
	{
		int brickposition8[2][32] = { { 1,2,2,3,4,4,5,6,7,8,9,9,9,10,10,10,9,9,9,8,7,6,6,5,4,3,2,1,1,1,6,7 }, { 3,3,2,2,2,1,1,1,1,1,1,2,3,3,4,5,5,6,7,7,7,7,6,6,6,6,6,6,5,4,3,3 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 31; j++)
			{
				brickposition[i][j] = brickposition8[i][j];
			}
		}

		int boxposition8[2][5] = { { 5,4,6,5,7 }, { 3,4,4,5,5 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 4; j++)
			{
				boxposition[i][j] = boxposition8[i][j];			//载入第八关箱子初始位置
			}
		}

		int aimposition8[2][5] = { { 3,2,3,2,3 }, { 3,4,4,5,5 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 4; j++)
			{
				aimposition[i][j] = aimposition8[i][j];			//载入第八关箱子目标位置
			}
		}
		position_x = 9; position_y = 4;

		width = 10;
		high = 7;
		size = min(HIGH / (high + 2), HIGH / (width + 2));
		if (size % 2 == 0)
		{
			size = size;
		}
		else
		{
			size = size - 1;
		}
	}
	if (gamechoice == 9)	//第九关
	{
		int brickposition9[2][46] = { { 2,3,4,5,6,7,8,9,10,10,10,10,10,10,11,11,11,11,10,9,8,7,7,6,5,4,3,2,1,1,1,1,2,2,2,2,2,5,6,5,6,7,8,8,4,4 }, { 1,1,1,1,1,1,1,1,1,2,3,4,5,6,6,7,8,9,9,9,9,9,8,9,9,9,9,9,9,8,7,6,6,5,4,3,2,2,2,4,4,4,5,6,6,5 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 45; j++)
			{
				brickposition[i][j] = brickposition9[i][j];
			}
		}

		int boxposition9[2][6] = { { 6,3,9,3,6,9 }, { 3,4,4,7,7,7 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 5; j++)
			{
				boxposition[i][j] = boxposition9[i][j];			//载入第九关箱子初始位置
			}
		}

		int aimposition9[2][6] = { { 5,6,7,5,6,7 }, { 5,5,5,6,6,6 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 5; j++)
			{
				aimposition[i][j] = aimposition9[i][j];			//载入第九关箱子目标位置
			}
		}
		position_x = 9; position_y = 8;

		width = 11;
		high = 9;
		size = min(HIGH / (high + 2), HIGH / (width + 2));
		if (size % 2 == 0)
		{
			size = size;
		}
		else
		{
			size = size - 1;
		}
	}
	if (gamechoice == 10)	//第十关
	{
		int brickposition10[2][26] = { { 3,4,5,6,7,8,8,8,8,8,7,7,7,6,5,4,4,3,2,1,1,1,1,2,3,3 }, { 1,1,1,1,1,1,2,3,4,5,5,6,7,7,7,7,6,6,6,6,5,4,3,3,3,2 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 25; j++)
			{
				brickposition[i][j] = brickposition10[i][j];
			}
		}

		int boxposition10[2][5] = { { 4,5,6,4,3 }, { 3,3,3,4,5 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 4; j++)
			{
				boxposition[i][j] = boxposition10[i][j];			//载入第十关箱子初始位置
			}
		}

		int aimposition10[2][5] = { { 5,6,4,5,6 }, { 4,4,5,5,5 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 4; j++)
			{
				aimposition[i][j] = aimposition10[i][j];			//载入第十关箱子目标位置
			}
		}
		position_x = 2; position_y = 4;

		width = 8;
		high = 7;
		size = min(HIGH / (high + 2), HIGH / (width + 2));
		if (size % 2 == 0)
		{
			size = size;
		}
		else
		{
			size = size - 1;
		}
	}
}
void Updatewithoutinput()
{
	int i, j, success = 0;
	for (i = 0; aimposition[0][i] > 0; i++)
	{
		for (j = 0; boxposition[0][j] > 0; j++)
		{
			if (aimposition[0][i] == boxposition[0][j] && aimposition[1][i] == boxposition[1][j])
				success++;
		}
	}

	if (viewchoice == 3 && success == i)
	{
		if (levelsteps[0][gamechoice - 1] == 0)
		{
			levelsteps[0][gamechoice - 1] = 1;
			levelsteps[1][gamechoice - 1] = distance;
		}
		else if (levelsteps[0][gamechoice - 1] == 1)
		{
			levelsteps[0][gamechoice - 1] = min(levelsteps[1][gamechoice - 1], distance);
		}

		if (gamechoice < 10)
		{
			
			setbkcolor(BLACK);
			cleardevice();
			setcolor(RED);
			settextstyle(100, 0, _T("方正粗黑宋简体"));
			RECT r = { 0, 300, WIDTH, HIGH };
			drawtext(_T("恭喜过关!"), &r, DT_CENTER);
			r = { 0, 500, WIDTH, HIGH };
			drawtext(_T("键盘按任意键进入下一关!"), &r, DT_CENTER);
			FlushBatchDraw();
			_getch();
			gamechoice++;
			Mapreset();
		}
		if (gamechoice == 10)
		{
			setcolor(RED);
			settextstyle(100, 0, _T("方正粗黑宋简体"));
			RECT r = { 0, 300, WIDTH, HIGH };
			drawtext(_T("恭喜过关!"), &r, DT_CENTER);
			r = { 0, 400, WIDTH, HIGH };
			drawtext(_T("全部通过啦!"), &r, DT_CENTER);
			r = { 0, 500, WIDTH, HIGH };
			drawtext(_T("键盘按任意键返回到关卡选择界面"), &r, DT_CENTER);
			FlushBatchDraw();
			_getch();
			viewchoice = 1;
		}
	}
}
void Updatewithinput()
{
	int i, j;//1，上，2，下，3，左，4，右
	if ((GetAsyncKeyState(VK_CONTROL) & 0x8000))
	{
		if ((GetAsyncKeyState(0x57) & 0x8000))
		{
			Goodbye();
		}
	}
	switch (viewchoice)
	{
	case 1:
	{
		if (MouseHit())
		{
			MOUSEMSG m;
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				if (m.x >= WIDTH / 2 - 140 && m.x <= WIDTH / 2 + 120 && m.y >= 520 && m.y <= 620)
				{
					viewchoice = 2;
				}
			}
		}
		break;
	}
	case 2:
	{
		if (MouseHit())
		{
			MOUSEMSG m;
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{

				//按下返回标志或者返回文字
				if (m.x >= 110 && m.x <= 198 && m.y >= 40 && m.y <= 158)
				{
					viewchoice = 1;
				}

				//按下关卡图形选择关卡
				for (i = 1; i <= 3; i++)
				{
					for (j = 1; j <= 3; j++)
					{
						if (m.x >= i / 4.0 * WIDTH - SIZE && m.x <= i / 4.0 * WIDTH + SIZE && m.y >= 200 + (j - 1) * 140 && m.y <= 300 + (j - 1) * 140)
						{

							viewchoice = 3;
							gamechoice = 3 * (j - 1) + i;
							Mapreset();
						}
					}
				}
				if (m.x >= 1 / 4.0 * WIDTH - SIZE && m.x <= 1 / 4.0 * WIDTH + SIZE && m.y >= 200 + (j - 1) * 140 && m.y <= 300 + (j - 1) * 140)
				{
					viewchoice = 3;
					gamechoice = 10;
					Mapreset();
				}
			}
		}
		break;
	}
	case 3:
	{
		if (MouseHit())
		{
			MOUSEMSG m;
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				if (m.x >= (WIDTH / size - 3) * size && m.x <= (WIDTH / size - 2) *size && m.y >= (HIGH / size - 3.5) * size && m.y <= (HIGH / size - 2.5) * size)
				{
					movechoice = 1;
					movetype = Move(movechoice);
				}
				if (m.x >= (WIDTH / size - 3) * size && m.x <= (WIDTH / size - 2) * size && m.y >= (HIGH / size - 2) * size && m.y <= (HIGH / size - 1) * size)
				{
					movechoice = 2;
					movetype = Move(movechoice);
				}
				if (m.x >= (WIDTH / size - 4.5) * size && m.x <= (WIDTH / size - 3.5) * size && m.y >= (HIGH / size - 2) * size && m.y <= (HIGH / size - 1) * size)
				{
					movechoice = 3;
					movetype = Move(movechoice);
				}
				if (m.x >= (WIDTH / size - 1.5) * size && m.x <= (WIDTH / size - 0.5) * size && m.y >= (HIGH / size - 2) * size && m.y <= (HIGH / size - 1) * size)
				{
					movechoice = 4;
					movetype = Move(movechoice);
				}
				if (m.x >= 850 && m.x <= 850 + 3 * SIZE && m.y >= 350 && m.y <= 350 + 3 * SIZE * 128 / 268)//返回主界面
				{
					viewchoice = 2;
				}
				if (m.x >= 850 && m.x <= 850 + 3 * SIZE && m.y >= 450 && m.y <= 450 + 3 * SIZE * 128 / 268)//重置
				{
					Mapreset();
				}
				if (m.x >= 850 && m.x <= 850 + 3 * SIZE && m.y >= 550 && m.y <= 550 + 3 * SIZE * 128 / 268)//撤销
				{
					if (redotimes > 0)
					{
						if (movechoice == 1)//撤销上移
						{
							if (movetype == 1)
							{
								redotimes--;
								movetype = 0;
								position_y++;
								distance--;
							}
							if (movetype == 2)
							{
								redotimes--;
								movetype = 0;
								position_y++;
								for (i = 0; boxposition[0][i] > 0; i++)
								{
									if (boxposition[1][i] == position_y - 2 && boxposition[0][i] == position_x)
									{
										boxposition[1][i]++;
										distance--;
									}
								}
							}
						}
						if (movechoice == 2)//撤销下移
						{
							if (movetype == 1)
							{
								redotimes--;
								movetype = 0;
								position_y--;
								distance--;
							}
							if (movetype == 2)
							{
								redotimes--;
								movetype = 0;
								position_y--;
								for (i = 0; boxposition[0][i] > 0; i++)
								{
									if (boxposition[1][i] == position_y + 2 && boxposition[0][i] == position_x)
									{
										boxposition[1][i]--;
										distance--;
									}
								}
							}
						}
						if (movechoice == 3)//撤销左移
						{
							if (movetype == 1)
							{
								redotimes--;
								movetype = 0;
								position_x++;
								distance--;
							}
							if (movetype == 2)
							{
								redotimes--;
								movetype = 0;
								position_x++;
								for (i = 0; boxposition[0][i] > 0; i++)
								{
									if (boxposition[1][i] == position_y && boxposition[0][i] == position_x - 2)
									{
										boxposition[0][i]++;
										distance--;
									}
								}
							}
						}
						if (movechoice == 4)//撤销右移
						{
							if (movetype == 1)
							{
								movetype = 0;
								redotimes--;
								position_x--;
								distance--;
							}
							if (movetype == 2)
							{
								movetype = 0;
								redotimes--;
								position_x--;
								for (i = 0; boxposition[0][i] > 0; i++)
								{
									if (boxposition[1][i] == position_y && boxposition[0][i] == position_x + 2)
									{
										boxposition[0][i]--;
										distance--;
									}
								}
							}
						}
					}
				}
			}
		}
		if (_kbhit())
		{
			int input1;
			input1 = _getch();
			if (input1 == 56 || input1 == 119 || input1 == 72)
			{
				movechoice = 1;
				movetype = Move(movechoice);
			}
			if (input1 == 50 || input1 == 115 || input1 == 80)
			{
				movechoice = 2;
				movetype = Move(movechoice);
			}
			if (input1 == 52 || input1 == 97 || input1 == 75)
			{
				movechoice = 3;
				movetype = Move(movechoice);
			}
			if (input1 == 54 || input1 == 100 || input1 == 77)
			{
				movechoice = 4;
				movetype = Move(movechoice);
			}
		}
		break;
	}
	}
}
int Move(int movechoice)//返回值为movetype，返回0代表无动作，返回1代表人自己动，返回2代表人和箱子都动
{
	int i, j, specialbox = -1;//记录box下标
	if (movechoice == 1)
	{
		specialbox = -1;
		for (i = 0; brickposition[0][i] > 0; i++)
		{
			//人前进前一个位置是墙
			if (brickposition[1][i] == position_y - 1 && brickposition[0][i] == position_x)
				return 0;
		}

		//判断人上方是否有箱子，若有，记录箱子下标
		for (i = 0; boxposition[0][i] > 0; i++)
		{
			if (boxposition[1][i] == position_y - 1 && boxposition[0][i] == position_x)
				specialbox = i;
		}
		if (specialbox == -1)//上方位置无箱子，代表人自己动
		{
			position_y--;
			distance++;
			return 1;
		}
		else//上方有箱子
		{
			for (i = 0; boxposition[0][i] > 0; i++)
			{
				//上方连着两个箱子
				if (boxposition[1][i] == boxposition[1][specialbox] - 1 && boxposition[0][i] == boxposition[0][specialbox])
					return 0;
			}
			for (j = 0; brickposition[0][j] > 0; j++)
			{
				//上方箱子有墙
				if (brickposition[1][j] == boxposition[1][specialbox] - 1 && brickposition[0][j] == boxposition[0][specialbox])
					return 0;
			}
			//人和箱子都向上
			position_y--;
			for (i = 0; boxposition[0][i] > 0; i++)
			{
				if (boxposition[1][i] == position_y && boxposition[0][i] == position_x)
				{
					boxposition[1][i]--;
					distance++;
					return 2;
				}
			}
		}

	}
	if (movechoice == 2)
	{
		specialbox = -1;

		for (i = 0; brickposition[0][i] > 0; i++)
		{
			//人前进前一个位置是墙
			if (brickposition[1][i] == position_y + 1 && brickposition[0][i] == position_x)
				return 0;
		}

		//判断人下方是否有箱子，若有记录箱子下标
		for (i = 0; boxposition[0][i] > 0; i++)
		{
			if (boxposition[1][i] == position_y + 1 && boxposition[0][i] == position_x)
				specialbox = i;
		}
		if (specialbox == -1)//下方位置无箱子，代表人自己动
		{
			position_y++;
			distance++;
			return 1;
		}
		else//下方有箱子
		{
			for (i = 0; boxposition[0][i] > 0; i++)
			{
				//下方连着两个箱子
				if (boxposition[1][i] == boxposition[1][specialbox] + 1 && boxposition[0][i] == boxposition[0][specialbox])
					return 0;
			}


			for (j = 0; brickposition[0][j] > 0; j++)
			{
				//下方箱子有墙
				if (brickposition[1][j] == boxposition[1][specialbox] + 1 && brickposition[0][j] == boxposition[0][specialbox])
					return 0;
			}

			//人和箱子都向下
			position_y++;
			for (i = 0; boxposition[0][i] > 0; i++)
			{
				if (boxposition[1][i] == position_y && boxposition[0][i] == position_x)
				{
					boxposition[1][i]++;
					distance++;
					return 2;
				}
			}

		}
	}
	if (movechoice == 3)
	{
		specialbox = -1;

		for (i = 0; brickposition[0][i] > 0; i++)
		{
			//人前进前一个位置是墙
			if (brickposition[0][i] == position_x - 1 && brickposition[1][i] == position_y)
				return 0;
		}

		//判断人左方是否有箱子，若有记录箱子下标
		for (i = 0; boxposition[0][i] > 0; i++)
		{
			if (boxposition[0][i] == position_x - 1 && boxposition[1][i] == position_y)
				specialbox = i;
		}
		if (specialbox == -1)//左方位置无箱子，代表人自己动
		{
			position_x--;
			distance++;
			return 1;
		}
		else//左方有箱子
		{
			for (i = 0; boxposition[0][i] > 0; i++)
			{
				//左方连着两个箱子
				if (boxposition[0][i] == boxposition[0][specialbox] - 1 && boxposition[1][i] == boxposition[1][specialbox])
					return 0;
			}


			for (j = 0; brickposition[0][j] > 0; j++)
			{
				//左方箱子有墙
				if (brickposition[0][j] == boxposition[0][specialbox] - 1 && brickposition[1][j] == boxposition[1][specialbox])
					return 0;
			}

			//人和箱子都向左
			position_x--;
			for (i = 0; boxposition[0][i] > 0; i++)
			{
				if (boxposition[1][i] == position_y && boxposition[0][i] == position_x)
				{
					boxposition[0][i]--;
					distance++;
					return 2;
				}
			}

		}
	}
	if (movechoice == 4)
	{
		specialbox = -1;

		for (i = 0; brickposition[0][i] > 0; i++)
		{
			//人前进前一个位置是墙
			if (brickposition[0][i] == position_x + 1 && brickposition[1][i] == position_y)
				return 0;
		}

		//判断人右方是否有箱子，若有记录箱子下标
		for (i = 0; boxposition[0][i] > 0; i++)
		{
			if (boxposition[0][i] == position_x + 1 && boxposition[1][i] == position_y)
				specialbox = i;
		}
		if (specialbox == -1)//右方位置无箱子，代表人自己动
		{
			position_x++;
			distance++;
			return 1;
		}
		else//右方有箱子
		{
			for (i = 0; boxposition[0][i] > 0; i++)
			{
				//右方连着两个箱子
				if (boxposition[0][i] == boxposition[0][specialbox] + 1 && boxposition[1][i] == boxposition[1][specialbox])
					return 0;
			}

			for (j = 0; brickposition[0][j] > 0; j++)
			{
				//右方箱子有墙
				if (brickposition[0][j] == boxposition[0][specialbox] + 1 && brickposition[1][j] == boxposition[1][specialbox])
					return 0;
			}

			//人和箱子都向右
			position_x++;
			for (i = 0; boxposition[0][i] > 0; i++)
			{
				if (boxposition[1][i] == position_y && boxposition[0][i] == position_x)
				{
					boxposition[0][i]++;
					distance++;
					return 2;
				}
			}

		}
	}
}
int Goodbye()
{
	int i, j = 0, k = 0;
	for (i = 0; i <= 9; i++)
	{
		if (levelsteps[0][i] == 1)
		{
			j++;
			k = k + levelsteps[1][i];
		}
	}

	SYSTEMTIME time2;
	GetLocalTime(&time2);
	int playtime;
	playtime = time2.wDay * 86400 + time2.wHour * 3600 + time2.wMinute * 60 + time2.wSecond - time1.wDay * 86400 - time1.wHour * 3600 - time1.wMinute * 60 - time1.wSecond;
	int hourtime, minutetime, secondtime;
	hourtime = playtime / 3600;
	minutetime = (playtime - hourtime * 3600) / 60;
	secondtime = playtime - hourtime * 3600 - minutetime * 60;

	setbkcolor(BLACK);
	cleardevice();
	settextstyle(96, 0, _T("方正粗黑宋简体"));

	settextcolor(RGB(255, 255, 255));
	outtextxy(200, 100, "本次您游戏时间为");

	char string[16] = { 0 };
	_itoa_s(hourtime, string, 10);
	settextcolor(RGB(250, 245, 240));
	outtextxy(300, 250, string);

	settextcolor(RGB(245, 235, 225));
	outtextxy(450, 250, "小时");

	_itoa_s(minutetime, string, 10);
	settextcolor(RGB(240, 225, 210));
	outtextxy(650, 250, string);

	settextcolor(RGB(235, 215, 195));
	outtextxy(800, 250, "分钟");

	_itoa_s(secondtime, string, 10);
	outtextxy(1000, 250, string);
	settextcolor(RGB(230, 205, 180));
	outtextxy(1150, 250, "秒");

	settextcolor(RGB(225, 195, 165));
	outtextxy(200, 400, "共通过");

	_itoa_s(j, string, 10);
	settextcolor(RGB(220, 185, 150));
	outtextxy(500, 400, string);

	settextcolor(RGB(215, 175, 135));
	outtextxy(650, 400, "关，共计");

	_itoa_s(k, string, 10);
	settextcolor(RGB(210, 165, 120));
	outtextxy(1000, 400, string);

	settextcolor(RGB(205, 155, 105));
	outtextxy(1200, 400, "步数");

	settextcolor(RGB(200, 145, 90));
	outtextxy(200, 550, "你真厉害，快去休息一下吧！！！");

	settextcolor(RGB(195, 135, 75));
	outtextxy(200, 700, "按任意键退出");
	EndBatchDraw();

	_getch();
	_getch();
	closegraph();
	exit(0);
	return 0;
}

