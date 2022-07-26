//#include<iostream>
//#include <iomanip>
//#include<string>
//using namespace std;
//class Matrix_4x4
//{
//private:
//	double matrix[4][4];
//public:
//	//默认构造函数，初始化矩阵为单位阵
//	Matrix_4x4()
//	{
//		for (int i = 0; i < 4; i++)
//			for (int j = 0; j < 4; j++)
//				matrix[i][j] = 0;
//		for (int i = 0; i < 4; i++)matrix[i][i] = 1;
//	};
//	//带参数构造函数，用一个4x4的二维数组初始化
//	Matrix_4x4(double a[4][4])
//	{
//		for (int i = 0; i < 4; i++)
//			for (int j = 0; j < 4; j++)
//				matrix[i][j] = a[i][j];
//	};
//	//拷贝构造函数
//	Matrix_4x4(const Matrix_4x4& a)
//	{
//		for (int i = 0; i < 4; i++)
//			for (int j = 0; j < 4; j++)
//				matrix[i][j] = a.matrix[i][j];
//	}
//	//重载 = 运算符，参数为矩阵对象
//	Matrix_4x4 operator=(const Matrix_4x4& a)
//	{
//		if (&a == this)return *this;
//		for (int i = 0; i < 4; i++)
//			for (int j = 0; j < 4; j++)
//				matrix[i][j] = a.matrix[i][j];
//		return *this;
//	}
//	//重载 = 运算符，参数为一个4x4的二维数组
//	Matrix_4x4 operator=(double a[4][4])
//	{
//		for (int i = 0; i < 4; i++)
//			for (int j = 0; j < 4; j++)
//				matrix[i][j] = a[i][j];
//		return *this;
//	}
//	// 重载算术运算符 + - * ^
//	friend Matrix_4x4 operator+(const Matrix_4x4& a, const Matrix_4x4& b);
//	friend Matrix_4x4 operator-(const Matrix_4x4& a, const Matrix_4x4& b);
//	friend Matrix_4x4 operator*(const Matrix_4x4& a, const Matrix_4x4& b);
//	friend Matrix_4x4 operator^(const Matrix_4x4& a, int n);
//	// 重载 [ ] 运算符，实现双下标方式访问矩阵元素（该功能已经实现，无需自己写）
//	const double* operator[] (const int i) const { return matrix[i]; }
//	double* operator[] (const int i) { return matrix[i]; }
//	// 重载输入<< 和输出 >>
//	friend ostream& operator <<(ostream& output, Matrix_4x4& a)
//	{
//		for (int i = 0; i < 4; i++)
//		{
//			for (int j = 0; j < 4; j++)
//			{
//				output.fill(' ');
//				output.width(20);
//				output.precision(8);
//				output << a.matrix[i][j];
//			}
//			output << endl;
//		}
//		output << endl;
//		return output;
//	}
//	friend istream& operator >>(istream& input, Matrix_4x4& a)
//	{
//		for (int i = 0; i < 4; i++)
//		{
//			for (int j = 0; j < 4; j++)
//				input >> a.matrix[i][j];
//		}
//		return input;
//	}
//	//矩阵转置，不改变当前矩阵值，返回转置矩阵
//	Matrix_4x4 transpose();
//
//
//
//	//矩阵求逆，不改变当前矩阵值，返回逆矩阵
//	Matrix_4x4 inverse();
//	//line2行加到line1行 以及对角线元化为1
//	void add_multiply(Matrix_4x4& a, int line1 = -1, int line2 = -1);
//	//行变换将line，col位置的元置为0
//	void to0(Matrix_4x4& a, int line, int col);
//
//};
//Matrix_4x4 operator+(const Matrix_4x4& a, const Matrix_4x4& b)
//{
//	Matrix_4x4 c;
//	for (int i = 0; i < 4; i++)
//		for (int j = 0; j < 4; j++)
//			c.matrix[i][j] = a.matrix[i][j] + b.matrix[i][j];
//	return c;
//}
//Matrix_4x4 operator-(const Matrix_4x4& a, const Matrix_4x4& b)
//{
//	Matrix_4x4 c;
//	for (int i = 0; i < 4; i++)
//		for (int j = 0; j < 4; j++)
//			c.matrix[i][j] = a.matrix[i][j] - b.matrix[i][j];
//	return c;
//}
//Matrix_4x4 operator*(const Matrix_4x4& a, const Matrix_4x4& b)
//{
//	Matrix_4x4 c;
//	for (int i = 0; i < 4; i++)
//		for (int j = 0; j < 4; j++)
//		{
//			double sum = 0;
//			for (int k = 0; k < 4; k++)
//				sum += a.matrix[i][k] * b.matrix[k][j];
//			c.matrix[i][j] = sum;
//		}
//	return c;
//}
//Matrix_4x4 operator^(Matrix_4x4& a, int n)
//{
//	if (n >= 0)
//	{
//		Matrix_4x4 b;
//		for (int i = 1; i <= n; i++)
//			b = b * a;
//		return b;
//	}
//	else
//	{
//		Matrix_4x4 b;
//		for (int i = 1; i <= -n; i++)
//			b = b * a.inverse();
//		return b;
//	}
//}
//Matrix_4x4 Matrix_4x4::transpose()
//{
//	Matrix_4x4 a;
//	for (int i = 0; i < 4; i++)
//		for (int j = 0; j < 4; j++)
//			a.matrix[i][j] = matrix[j][i];
//	return a;
//}
//Matrix_4x4 Matrix_4x4::inverse()
//{
//	Matrix_4x4 copy(*this);
//	Matrix_4x4 eye;
//	double temp[4] = { 0 };
//
//	//实现下三角为0，对角线为0
//	for (int i = 0; i < 4; i++)
//	{
//		if (matrix[i][i] == 0)//对角线元为0
//		{
//			for (int j = 0; j < 4; j++)
//			{
//				if (matrix[j][i] != 0)
//				{
//					copy.add_multiply(eye, i, j);
//				}
//			}
//		}
//		copy.add_multiply(eye, i);//主对角线元化为1
//		for (int j = i + 1; j < 4; j++)//主元以下化为0
//			copy.to0(eye, j, i);
//	}
//	//实现上三角为0
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = i - 1; j >= 0; j--)//主元以上化为0
//			copy.to0(eye, j, i);
//	}
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			if (i == j)
//				if (copy.matrix[i][j] != 1)
//					exit(1);
//			if (i != j)
//				if (copy.matrix[i][j] != 0)
//					exit(1);
//		}
//
//	}
//	return eye;
//}
//void Matrix_4x4::to0(Matrix_4x4& a, int line, int col)
//{
//	if (line == col)return;
//	double temp = matrix[line][col] / matrix[col][col];
//	for (int i = 0; i < 4; i++)
//	{
//		matrix[line][i] -= temp * matrix[col][i];
//		a.matrix[line][i] -= temp * a.matrix[col][i];
//	}
//}
//void Matrix_4x4::add_multiply(Matrix_4x4& a, int line1, int line2)
//{
//	if (line2 != -1)//line2加到line1
//	{
//		for (int i = 0; i < 4; i++)
//		{
//			matrix[line1][i] += matrix[line2][i];
//			a.matrix[line1][i] += a.matrix[line2][i];
//		}
//	}
//	else//将第line1行主元变成1
//	{
//		double temp = matrix[line1][line1];
//		for (int i = 0; i < 4; i++)
//		{
//			matrix[line1][i] /= temp;
//			a.matrix[line1][i] /= temp;
//		}
//	}
//}
//int main()
//{
//	double	n[4][4] = { { 1,2,3,5 },{ 6,3,2,1},{ 4,3,5,2},{6,1,3,8} };
//	Matrix_4x4 e(n);
//	Matrix_4x4 d;
//	d = e.inverse();
//	d = e.inverse();
//	cout << e << endl;
//	cout << "e.inverse();" << endl << "e.inverse()= " << endl << d << endl;
//	while (!getchar());
//	return 0;
//}