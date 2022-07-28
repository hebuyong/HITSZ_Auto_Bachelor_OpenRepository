#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<Windows.h>
#include<graphics.h>
#include"function.h"

int main()
{
	startup();
	while (1)
	{
		Show();
		Updatewithoutinput();
		Updatewithinput();
	}
	goodbye();
}
