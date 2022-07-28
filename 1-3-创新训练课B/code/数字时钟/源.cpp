#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<math.h>
#include<iostream>
using namespace std;
#define High 480
#define Width 480
#define PI 3.14159265

int main()
{
	initgraph(Width, High);
	BeginBatchDraw();
	SYSTEMTIME ti;
	int i, j, k;
	double endxy[6];
	double angle[3];
	double length[3] = { High / 3,High / 4,High / 5 };
	int center_x = Width / 2;
	int center_y = High / 2;
	double xy[6], angletemp = 0;
	while (1)
	{
		GetLocalTime(&ti);
		setcolor(WHITE);
		setlinestyle(PS_SOLID, 2);
		circle(center_x, center_y, Width / 2 - 40);
		angle[0] = double(ti.wSecond) * 2 * PI / 60;
		angle[1] = (double(ti.wMinute) * 60.0 + double(ti.wSecond)) * 2 * PI / 60 / 60;
		angle[2] = (double(ti.wHour) * 60.0 * 60 + double(ti.wMinute) * 60 + double(ti.wSecond)) * 2 * PI / 12 / 60 / 60;
		for (i = 0; i <= 2; i++)
		{
			endxy[2 * i] = center_x + length[i] * sin(angle[i]);
			endxy[2 * i + 1] = center_y - length[i] * cos(angle[i]);
		}
		char str1[] = "my watch";
		outtextxy(center_x - 30, High - 100, str1);
		char str2 = ':';
		int a = int(ti.wHour);
		snprintf(str1, sizeof(str1), "%d", a);
		if (str1[1] == '\0')
		{
			str1[2] = '\0';
			str1[1] = str1[0];
			str1[0] = '0';
		}
		outtextxy(205, 350, str1);
		outtextxy(225, 350, str2);
		a = int(ti.wMinute);
		snprintf(str1, sizeof(str1), "%d", a);
		if (str1[1] == '\0')
		{
			str1[2] = '\0';
			str1[1] = str1[0];
			str1[0] = '0';
		}
		outtextxy(235, 350, str1);
		outtextxy(255, 350, str2);
		a = int(ti.wSecond);
		snprintf(str1, sizeof(str1), "%d", a);
		if (str1[1] == '\0')
		{
			str1[2] = '\0';
			str1[1] = str1[0];
			str1[0] = '0';
		}
		outtextxy(265, 350, str1);

		setcolor(WHITE);
		setlinestyle(PS_SOLID, 2);
		line(center_x, center_y, int(endxy[0]), int(endxy[1]));
		setcolor(YELLOW);
		setlinestyle(PS_SOLID, 4);
		line(center_x, center_y, int(endxy[2]), int(endxy[3]));
		setcolor(RED);
		setlinestyle(PS_SOLID, 8);
		line(center_x, center_y, int(endxy[4]), int(endxy[5]));
		setcolor(WHITE);
		setfillcolor(WHITE);
		fillcircle(center_x, center_y, 10);
		for (i = 1; i <= 4; i++)
		{
			xy[2] = center_x + (double(Width) / 2 - 60) * sin(angletemp);
			xy[3] = center_y - (double(Width) / 2 - 60) * cos(angletemp);
			xy[0] = xy[2] - 5;
			xy[1] = xy[3] - 5;
			xy[4] = xy[2] + 5;
			xy[5] = xy[3] + 5;
			setlinestyle(PS_SOLID, 1);
			circle(int(xy[2]), int(xy[3]), 5);
			angletemp += PI / 30;
			xy[2] = center_x + (double(Width) / 2 - 60) * sin(angletemp);
			xy[3] = center_y - (double(Width) / 2 - 60) * cos(angletemp);
			xy[0] = xy[2] - 5;
			xy[1] = xy[3] - 5;
			xy[4] = xy[2] + 5;
			xy[5] = xy[3] + 5;
			for (j = 1; j <= 3; j++)
			{
				for (k = 1; k <= 4; k++)
				{
					circle(int(xy[2]), int(xy[3]), 2);
					angletemp += PI / 30;
					xy[2] = center_x + (double(Width) / 2 - 60) * sin(angletemp);
					xy[3] = center_y - (double(Width) / 2 - 60) * cos(angletemp);
					xy[0] = xy[2] - 5;
					xy[1] = xy[3] - 5;
					xy[4] = xy[2] + 5;
					xy[5] = xy[3] + 5;
				}
				if (j == 1 || j == 2)
				{
					fillrectangle(int(xy[0]), int(xy[1]), int(xy[4]), int(xy[5]));

					angletemp += PI / 30;
					xy[2] = center_x + (double(Width) / 2 - 60) * sin(angletemp);
					xy[3] = center_y - (double(Width) / 2 - 60) * cos(angletemp);
					xy[0] = xy[2] - 5;
					xy[1] = xy[3] - 5;
					xy[4] = xy[2] + 5;
					xy[5] = xy[3] + 5;
				}
			}
		}
		FlushBatchDraw();
		Sleep(0);
		setcolor(BLACK);
		setlinestyle(PS_SOLID, 2);
		line(center_x, center_y, int(endxy[0]), int(endxy[1]));
		setcolor(BLACK);
		setlinestyle(PS_SOLID, 4);
		line(center_x, center_y, int(endxy[2]), int(endxy[3]));
		setcolor(BLACK);
		setlinestyle(PS_SOLID, 8);
		line(center_x, center_y, int(endxy[4]), int(endxy[5]));
	}
	_getch();
	closegraph();
	return 0;
}