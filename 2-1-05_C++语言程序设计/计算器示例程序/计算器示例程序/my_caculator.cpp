#include <iostream>
#include <stdio.h>
#include <string>
#include "my_caculator.h"
using namespace std;
//构造函数，控制台提示用户输入四则表达式，表达式包含字符0-9,+,-,*,/,(,),[,],{,},且为英文字符
Caculator::Caculator()
{
    cout << "please input the expression"<<endl;
    string temp_string;
    getline(cin, temp_string);
    expression_ = temp_string;
    cout << "the expression is "<< expression_<<endl;
}
//带参构造函数，传入四则表达式字符串
//input: string
Caculator::Caculator(string str)
{
    expression_ = str;
    cout << "the expression is "<< expression_<<endl;
}

Caculator::~Caculator()
{
    //dtor
}
//实现四则表达式中数值与操作符的识别，和括号匹配的判断
int Caculator::output_num_opt_and_check_balance()
{
    //创建空栈，用于存放括号
    MyStack<char> brackets_stack;
    //遍历string表达式
    for(int i=0; i<expression_.length()-1; i++)
    {
        //如果为0-9.字符，则将其存放入数组中，直到遇到非0-9.字符
        if(isNum(expression_[i]))
        {
            char member[16]={0};//存放数字字符的数组
            int m = 0;
            while(isNum(expression_[i]))
            {
                member[m++] = expression_[i++];
            }
            //将得到的数字字符数组转变为double型值
            double num = str_to_num(member);
            //double num = std::stod(member);
            cout <<"操作数:"<<num<<endl;
        }

        if(isOpt(expression_[i]))
        {
            cout <<"操作符:"<<expression_[i]<<endl;
            //如果是左括号,则将其存入brackets_stack中
            if(expression_[i]=='(' || expression_[i]=='['||expression_[i]=='{')
            {
                brackets_stack.push(expression_[i]);
            }

            if(expression_[i]==')' || expression_[i]==']'||expression_[i]=='}')
            {
                //如果是右括号，且栈为空，则匹配错误
                if(brackets_stack.isEmpty())
                {
                     cout<<"括号匹配错误"<<endl;
                     exit(0);
                }

                else
                {
                    //如果是右括号，且栈顶元素与该右括号匹配，则弹出栈顶元素
                    char temp = brackets_stack.getTop();
                    if(isPair(temp,expression_[i]))
                    {
                        brackets_stack.pop();
                        continue;
                    }
                    //如果是右括号，且栈顶元素与该右括号不匹配，则匹配错误
                    else
                    {
                        cout <<"括号匹配错误"<<endl;
                        exit(0);
                    }

                }
            }
        }
        //如果检测到非数字非操作符字符，则提示非法表达式
        if(!isOpt(expression_[i]) && !isNum(expression_[i]) && expression_[i] != 0)
        {
            cout <<"illegale expression:"<<expression_[i]<<endl;
            exit(0);
        }
    }
    //所有字符读取结束后，若栈不为空，表示有未匹配的左括号，匹配错误
    if(!brackets_stack.isEmpty())
    {
         cout<<"括号匹配错误"<<endl;
         exit(0);
    }

}
//计算并返回四则表达式的值
double Caculator::get_caculation_result()
{
    MyStack<char> opt_stack;//创建操作符栈
    MyStack<double> num_stack;//创建操作数栈

    double num1,num2;
    char opt;

    for(int i=0; i<expression_.length(); i++)
    {
        //如果读到的是操作数，则压入操作数栈
        if(isNum(expression_[i]))
        {
            char member[16]={0};
            int m = 0;
            do
            {
                member[m++] = expression_[i++];
            }
            while(isNum(expression_[i]));

            double num = str_to_num(member);
            //double num = std::stod(member);
            num_stack.push(num);
        }
        //如果读到的是操作符
        if(isOpt(expression_[i]))
        {
            //如果读到的操作符是右括号，则依次弹出操作符栈元素，直至遇到相匹配的左括号
            if(expression_[i] == ')' || expression_[i] == ']' || expression_[i] == '}' )
            {
                while(!isPair(opt_stack.getTop(), expression_[i]))
                {
                    opt=opt_stack.pop();
                    //每弹出一个操作符，则从操作数栈弹出两个操作数，进行运算后，结果压入操作数栈
                    num1=num_stack.pop();
                    num2=num_stack.pop();
                    double temp_result = compute(num2,num1,opt);
                    num_stack.push(temp_result);
                }
                //弹出相匹配的左括号
                opt_stack.pop();
            }
            else
            {
                //如果操作符栈为空，或者操作符栈顶的符号优先级小，则将读到的操作符压入操作符栈
                if (opt_stack.isEmpty() || PriorityTable(expression_[i])>PriorityTable(opt_stack.getTop()))
                {
                    opt_stack.push(expression_[i]);
                }
                else
                {
                    //否则，依次弹出栈顶操作符，直至栈顶操作符优先级小于读到的操作符，或栈为空，或者栈顶元素为左括号
                    while(!opt_stack.isEmpty() && (PriorityTable(expression_[i])<=PriorityTable(opt_stack.getTop())) && opt_stack.getTop()!='(' && opt_stack.getTop()!='['&& opt_stack.getTop()!='{')
                    {
                        opt=opt_stack.pop();
                        num1 = num_stack.pop();
                        num2 = num_stack.pop();
                        double temp_result = compute(num2,num1,opt);
                        num_stack.push(temp_result);
                    }
                    //将读到的操作符入栈
                    opt_stack.push(expression_[i]);
                }
            }

        }
    }
    //读取结束，如果操作符栈中还有元素，则依次弹出，直至操作符栈为空
    while(!opt_stack.isEmpty())
    {
        opt = opt_stack.pop();
        num1 = num_stack.pop();
        num2 = num_stack.pop();
        double temp_result = compute(num2,num1,opt);
        num_stack.push(temp_result);
    }
    return num_stack.pop();
}



bool isNum(char c)
{
	return (c>='0' && c<='9' || c=='.');
}

bool isOpt(char c)
{
	return (c=='+' || c=='-' || c=='*' || c=='/' || c=='(' || c==')' || c=='[' || c==']'||c=='{' || c=='}') ;
}

bool isPair(char lc, char rc)
{
	return(lc=='('&&rc==')' || lc=='['&&rc==']' || lc=='{'&&rc=='}' );
}

double str_to_num(char *s)
{
	double num=0;
	bool decimal=0;
	double exp=0.1;

	while(*s)
	{
		if (*s=='.')
		{
			decimal=1;
			s++;
			continue;
		}

		if (!decimal)
		{
			num=num*10+(*s-'0');
		}
		else
		{
			num=num+(*s-'0')*exp;
			exp=exp*0.1;
		}
		s++;
	}
	return num;
}
int PriorityTable(char c)
{
	switch (c)
	{
	case '+':
	case '-':
		return 1;

	case '*':
	case '/':
		return 2;

	case '(':
    case '[':
    case '{':
		return 3;

	case ')':
    case ']':
    case '}':
		return -1;
	}
}

double compute(double a1, double a2, char opt)
{
	switch (opt)
	{
	case '+':
		return a1+a2;
	case '-':
		return a1-a2;
	case '*':
		return a1*a2;
	case '/':
		return a1/a2;
	}

}
