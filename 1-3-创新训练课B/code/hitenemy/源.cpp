#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<Windows.h>

void startup();
void Show();
void Updatewithoutinput();
void Updatewithinput();
void HideCursor();
void gotoxy(int x, int y);

int width = 30;
int high = 30;
static int num = 0;
int position_x, position_y, enemy_x, enemy_y, bullet_x, bullet_y, score = 0;
int main()
{
	startup();
	while (1)
	{
		Show();
		Updatewithoutinput();
		Updatewithinput();
	}
	return 0;
}
void startup()
{
	HideCursor();
	position_x = width / 2;
	position_y = high;
	bullet_x = 0;
	bullet_y = -1;
	enemy_x = width / 2;
	enemy_y = 1;
}
void Show()
{
	gotoxy(0, 0);   //«Â∆¡
	int i, j;
	for (i = 1; i <= high; i++)
	{
		for (j = 1; j <= width; j++)
		{
			if ((i == position_y) && (j == position_x))
				printf("*");
			if ((i == bullet_y) && (j == bullet_x))
				printf("|");
			if ((i == enemy_y) && (j == enemy_x))
				printf("$");
			else
				printf(" ");
		}
		printf("\n");
	}


}
void Updatewithoutinput()
{

	if (enemy_y > high)
	{
		enemy_y = 1;
		srand(time(NULL));
		enemy_x = rand() % width;
	}
	else
	{
		if (num < 10)
			num++;
		else
		{
			enemy_y++;
			num = 0;
		}
	}
	if (bullet_y > 0)
		bullet_y--;
	if ((bullet_x == enemy_x) && (bullet_y == enemy_y))
	{
		bullet_y = -1;
		enemy_y = high + 1;
		score++;
	}
	printf("score is %d", score);
}
void Updatewithinput()
{

	if (_kbhit())
	{
		char key = _getch();
		if (key == 'a')
			position_x--;
		if (key == 'd')
			position_x++;
		if (key == 's')
			position_y++;
		if (key == 'w')
			position_y--;
		if (key == ' ')
		{
			bullet_y = position_y - 1;
			bullet_x = position_x;
		}
	}
}
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD POS;
	POS.X = x;
	POS.Y = y;
	SetConsoleCursorPosition(handle, POS);
}
