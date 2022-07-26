#include<iostream>
#include<math.h>
#include<string>
#define length 100
using namespace std;

template<class type>
class stack
{
public:
	stack(type a)
	{
		for (int i = 0; i < length; i++)
		{
			link[i] = a;
		}
		//cout << "constructor" << endl;
	}
	type link[length];
};
void outputformat(string command, double num[], int brackets[], int n = length);
void spl(string command, double num[], int brackets[]);
void calcualte(string command, double num[], int brackets[]);
double calcualte_result(string command, double num[], int brackets[]);
double calcualte_simple(int n, double a, double b);
void reset(string command, double num[], int brackets[]);
int former(int i, string command, double num[]);
int later(int i, int j, string command, double num[]);

int main()
{
	string command;
	double num[length] = { 0 };
	int brackets[length] = { 0 }; //1-{,2-[,3-(,4-},5-],6-)
	for (;;)
	{
		reset(command, num, brackets);
		cout << "请输入简单四则运算算式:" << endl;
		//输入
		//{
		//	char a;
		//	int b = 61;
		//	int i = 0;
		//	for (;;)
		//	{
		//		a = getchar();
		//		b = a;
		//		if (b == 123 || b == 125 || b == 91 || b == 93\
		//			|| b == 40 || b == 41 || b == 46 || b == 43 || b == 45\
		//			|| b == 42 || b == 47 || (b >= 48 && b <= 57) || a == '=' || a == '\n')
		//		{
		//			if (a == '=' || a == '\n')
		//				break;
		//			//command[i] = a;
		//			i++;
		//		}
		//	}
		//}
		cin >> command;
		spl(command, num, brackets);
		calcualte(command, num, brackets);
		cout << endl;
	}
	return 0;
}
void reset(string command, double num[], int brackets[])
{
	int i, j;
	for (int i = 0; i < length; i++)
	{
		command = "";
		//num，brackets默认初值为0,'0'
		num[i] = 0;
		brackets[i] = 0;
	}
}

void spl(string command, double num[], int brackets[])
{

	for (int i = 0; i < command.size() && i < length; i++)
	{
		switch (command[i])
		{
		case '{':
			brackets[i] = 1;
			break;
		case '}':
			brackets[i] = 2;
			break;
		case '[':
			brackets[i] = 3;
			break;
		case ']':
			brackets[i] = 4;
			break;
		case '(':
			brackets[i] = 5;
			break;
		case ')':
			brackets[i] = 6;
			break;
		case '+':
			brackets[i] = 7;
			break;
		case '-':
			brackets[i] = 8;
			break;
		case '*':
			brackets[i] = 9;
			break;
		case '/':
			brackets[i] = 10;
			break;
		case '.':
			brackets[i] = 11;
			break;
		}
	}
	for (int i = 0; i < command.size() && i < length; i++)
	{
		int j, k;
		if (int(command[i]) >= 48 && int(command[i]) <= 57)
		{
			num[i] = command[i] - '0';
			j = former(i, command, num);
			k = later(i, j, command, num);
			if (k != 0)
				i = k;
			else
			{
				i = j;
				cout << "wrong\n";
				/*错误输出*/
			}

		}
	}

}

//小数点前数字处理
int former(int i, string command, double num[])
{
	int j;
	for (j = i + 1; j < command.size() && j < length; j++)
	{
		if (int(command[j]) >= 48 && int(command[j]) <= 57)
		{
			num[i] = num[i] * 10 + command[j] - '0';
		}
		else
			break;

	}
	return j;
}

//小数点后的数字处理
int later(int i, int j, string command, double num[])
{
	int k = 0;
	if (int(command[j]) == 46)
	{
		if (!(command[j + 1] >= 48 && command[j + 1] <= 57))
			return 0;
		else
		{
			for (int k = j + 1; k < command.size() && k < length; k++)
			{
				if (int(command[k]) >= 48 && int(command[k]) <= 57)
				{
					//cout<<num[i]<<"\t"<<command[k]-'0'<<"\t"<<double(pow(10,k-j))<<endl;
					num[i] = num[i] + (command[k] - '0') / double(pow(10, k - j));
					//最后为数字结尾
					if (k == command.size() - 1) return command.size() - 1;
				}
				else
					return k;
			}
		}
	}
	else
		return j;
	return j;
}

void calcualte(string command, double num[], int brackets[])
{
	int wrong = 0;
	//left从第二个存储位置开始存
	stack <int> left('0');
	int position = -1;
	//判断括号是否匹配
	for (int i = 0; i < command.size() && i < length; i++)
	{
		if (brackets[i] == 1 || brackets[i] == 3 || brackets[i] == 5)
		{
			left.link[position + 1] = brackets[i];
			position++;
		}
		if (brackets[i] == 2 || brackets[i] == 4 || brackets[i] == 6)
		{
			if (position == -1) { wrong = i; break; }
			if (brackets[i] == 2)
			{
				if (left.link[position] != 1)
				{
					wrong = i;
					break;
				}
				else
				{
					left.link[position] = 0;
					position--;
				}
			}
			if (brackets[i] == 4)
			{
				if (left.link[position] != 3)
				{
					wrong = i;
					break;
				}
				else
				{
					left.link[position] = 0;
					position--;
				}
			}
			if (brackets[i] == 6)
			{
				if (left.link[position] != 5)
				{
					wrong = i;
					break;
				}
				else
				{
					left.link[position] = 0;
					position--;
				}
			}
		}
	}

	//检测
	//for(int i=0;i<50;i++)
	//cout<<i<<"\t"<<left.link[i]<<"\t"<<wrong<<endl;

//{[10*5]*2.456+5.789*(1.45*100))
//{[10*5]*{[10*5]*2.456)+5.789*(1.45*100))
//{[10*5]*[{[10*5]*2.456+5.789*(1.45*100))
//5+7*3-(6*2+1)/10
	//cout<<position<<endl;
	if (wrong != 0)
	{
		outputformat(command, num, brackets, wrong);
		cout << "匹配错误" << endl;
	}
	else
	{
		if (position == -1)//正确，输出计算结果
		{
			double result = calcualte_result(command, num, brackets);
			if (result == 999.99)
				cout << "wrong" << endl;
			else
			{
				cout << command;
				cout << "=" << result << endl;
			}
		}
		else
		{
			outputformat(command, num, brackets);
			cout << "无法匹配" << endl;
		}
	}
}
double calcualte_result(string command, double num[], int brackets[])
{
	int order[11] = { 0,3,0,3,0,3,0,1,1,2,2 };//加减乘除7,8,9,10
	double result = 999.99;

	//操作符栈
	stack <int> oper(0);
	int position_oper = 0;
	//操作数栈
	stack <double> number(0);
	int position_number = 0;
	for (int i = 0; i < command.size() && i < length; i++)
	{
		if (num[i] != 0)//数值数组非0存入
		{
			number.link[position_number + 1] = num[i];
			position_number++;
		}
		if (brackets[i] != 0 && brackets[i] != 11)//操作符数组非0且非.存入
		{
			if (order[oper.link[position_oper]] < order[brackets[i]]|| order[oper.link[position_oper]] ==3)//优先级高于现栈顶优先级，压入
			{
				oper.link[position_oper + 1] = brackets[i];
				position_oper++;
			}
			else
			{
				if (brackets[i] == 2 || brackets[i] == 4 || brackets[i] == 6)
				{
					for (;;)
					{
						{
							for (int i = 1; i <= position_number; i++)
								cout << "操作数" << i << "\t" << number.link[i] << endl;
							for (int i = 1; i <= position_oper; i++)
								cout << "操作符" << i << "\t" << oper.link[i] << endl;
							cout << endl;
						}
						if (oper.link[position_oper] == brackets[i] - 1)
						{
							position_oper--;
							break;
						}
						else
						{
    							number.link[position_number - 1] = calcualte_simple(oper.link[position_oper], \
								number.link[position_number - 1], number.link[position_number]);
							position_number--; position_oper--;
							cout << oper.link[position_oper] << endl;
						}	
					}
				}
				else
				{

					if (position_number > 1)
					{
						if (position_oper > 0)
						{
							{
								for (int i = 1; i <= position_number; i++)
									cout << "操作数" << i << "\t" << number.link[i] << endl;
								for (int i = 1; i <= position_oper; i++)
									cout << "操作符" << i << "\t" << oper.link[i] << endl;
								cout << endl;
							}

							number.link[position_number - 1] = calcualte_simple(oper.link[position_oper], \
								number.link[position_number - 1], number.link[position_number]);
							position_number--; position_oper--;

							
						}
					}
					oper.link[position_oper + 1] = brackets[i];
					position_oper++;
				}
				
			}
		}
	}

	{
		for (int i = 1; i <= position_number; i++)
			cout << "操作数" << i << "\t" << number.link[i] << endl;
		for (int i = 1; i <= position_oper; i++)
			cout << "操作符" << i << "\t" << oper.link[i] << endl;
		cout << endl;
	}



	if (oper.link[position_oper] == 9|| oper.link[position_oper] == 10)
	{
		{
			for (int i = 1; i <= position_number; i++)
				cout << "操作数" << i << "\t" << number.link[i] << endl;
			for (int i = 1; i <= position_oper; i++)
				cout << "操作符" << i << "\t" << oper.link[i] << endl;
			cout << endl;
		}

		number.link[position_number - 1] = calcualte_simple(oper.link[position_oper], \
			number.link[position_number - 1], number.link[position_number]);
		position_number--; position_oper--;
	}
	
	
	{
		for (int i = 1; i <= position_number; i++)
			cout << "操作数" << i << "\t" << number.link[i] << endl;
		for (int i = 1; i <= position_oper; i++)
			cout << "操作符" << i << "\t" << oper.link[i] << endl;
		cout << endl;
	}

	for (int i = 1; i <= position_oper; i++)
	{
		cout << position_oper << endl;

		{
			for (int i = 1; i <= position_number; i++)
				cout << "操作数" << i << "\t" << number.link[i] << endl;
			for (int i = 1; i <= position_oper; i++)
				cout << "操作符" << i << "\t" << oper.link[i] << endl;
			cout << endl;
		}

   		number.link[i + 1] = calcualte_simple(oper.link[i], \
			number.link[i], number.link[i + 1]);

		{
			for (int i = 1; i <= position_number; i++)
				cout << "操作数" << i << "\t" << number.link[i] << endl;
			for (int i = 1; i <= position_oper; i++)
				cout << "操作符" << i << "\t" << oper.link[i] << endl;
			cout << endl;
		}


	}
	result = number.link[position_number];
	return result;
}
double calcualte_simple(int n, double a, double b)
{
	if (n == 7)return a + b;
	if (n == 8)return a - b;
	if (n == 9)return a * b;
	if (n == 10 && b != 0)return a / b;
	return 0;
}
void outputformat(string command, double num[], int brackets[], int n)
{
	for (int i = 0; i < command.size() && i < length && i <= n; i++)
	{
		if (num[i] != 0)
		{
			cout << "操作数:\t" << num[i] << endl;
		}
		if (brackets[i] != 0 && brackets[i] != 11)
		{
			switch (brackets[i])
			{
			case 1:
				cout << "操作符:\t左大括号\t";
				break;
			case 2:
				cout << "操作符:\t右大括号\t";
				break;
			case 3:
				cout << "操作符:\t左中括号\t";
				break;
			case 4:
				cout << "操作符:\t右中括号\t";
				break;
			case 5:
				cout << "操作符:\t左小括号\t";
				break;
			case 6:
				cout << "操作符:\t右小括号\t";
				break;
			case 7:
				cout << "操作符:\t加号\t";
				break;
			case 8:
				cout << "操作符:\t减号\t";
				break;
			case 9:
				cout << "操作符:\t乘号\t";
				break;
			case 10:
				cout << "操作符:\t除号\t";
				break;
			}
			if (i != n)cout << endl;
		}
	}
}