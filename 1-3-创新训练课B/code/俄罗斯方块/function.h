#pragma once
#define SIZE 66
#define W 10
#define H 10
#define WIDTH 700
#define HIGH 800

void startup();
void Show();
void Updatewithoutinput();
void Updatewithinput();
void boxstartup();//用于储存现有方块的信息矩阵初始化
int Move(int movekind);