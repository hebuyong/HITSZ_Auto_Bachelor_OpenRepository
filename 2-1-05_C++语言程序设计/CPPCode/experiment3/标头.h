//标头.h
#pragma once
class Matrix_4x4
{
private:
	double matrix[4][4];
public:
	//默认构造函数，初始化矩阵为单位阵
	Matrix_4x4();
	//带参数构造函数，用一个4x4的二维数组初始化
	Matrix_4x4(double a[4][4]);
	//拷贝构造函数
	Matrix_4x4(const Matrix_4x4& a);
	//重载 = 运算符，参数为矩阵对象

	//重载 = 运算符，参数为一个4x4的二维数组
	// 重载算术运算符 + - * 
	// 重载 ^ 运算符为矩阵的i次幂（如果i为负数，如何处理？）

	// 重载 [ ] 运算符，实现双下标方式访问矩阵元素（该功能已经实现，无需自己写）
	const double* operator[] (const int i) const { return matrix[i]; }
	double* operator[] (const int i) { return matrix[i]; }

	// 重载输入<< 和输出 >>
	friend ostream& operator <<(ostream& output, Matrix_4x4& a);
	

	Matrix_4x4 inverse();   //矩阵求逆，不改变当前矩阵值，返回逆矩阵
	Matrix_4x4 transpose(); //矩阵转置，不改变当前矩阵值，返回转置矩阵

	void disp();
};