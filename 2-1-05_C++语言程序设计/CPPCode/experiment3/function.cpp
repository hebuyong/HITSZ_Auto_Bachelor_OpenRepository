//function.cpp
#pragma once

#include<iostream>
#include<string>
#include "标头.h"
#define VNAME(value) (#value)

using namespace std;

//默认构造函数，初始化矩阵为单位阵
Matrix_4x4::Matrix_4x4()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			matrix[i][j] = 0;
	for (int i = 0; i < 4; i++)matrix[i][i] = 1;
};
//带参数构造函数，用一个4x4的二维数组初始化
Matrix_4x4::Matrix_4x4(double a[4][4])
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			matrix[i][j] = a[i][j];
};
//拷贝构造函数
Matrix_4x4::Matrix_4x4(const Matrix_4x4& a)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			matrix[i][j] = a.matrix[i][j];
}
//重载 = 运算符，参数为矩阵对象

//重载 = 运算符，参数为一个4x4的二维数组
// 重载算术运算符 + - * 
// 重载 ^ 运算符为矩阵的i次幂（如果i为负数，如何处理？）

// 重载输入>> 和输出 <<
ostream& operator <<(ostream& output, Matrix_4x4& a)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			output << "\t" << a.matrix[i][j];
		output << endl;
	}

	a.disp();
	//output << "F : " << D.feet << " I : " << D.inches;
	return output;
}



Matrix_4x4 Matrix_4x4::inverse()//矩阵求逆，不改变当前矩阵值，返回逆矩阵
{
	return Matrix_4x4();
}
Matrix_4x4 Matrix_4x4::transpose() //矩阵转置，不改变当前矩阵值，返回转置矩阵
{
	return Matrix_4x4();
}


void Matrix_4x4::disp()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << "\t" << matrix[i][j];
		cout << endl;
	}
}

