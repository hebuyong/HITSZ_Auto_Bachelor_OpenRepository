#ifndef MY_EXPRESSION_H
#define MY_EXPRESSION_H

#include <string>
#include "my_stack.hpp"
using namespace std;

class Caculator
{
    public:
        Caculator();//构造函数，控制台提示用户输入四则表达式，表达式包含字符0-9,+,-,*,/,(,),[,],{,},且为英文字符
        Caculator(string str);//带参构造函数，传入四则表达式字符串
        void output_num_opt_and_check_balance();//实现四则表达式中数值与操作符的识别，和括号匹配的判断
        double get_caculation_result();//计算并返回四则表达式的值
        virtual ~Caculator();

    protected:

    private:
        string expression_; //存储四则表达式字符串
};

bool isNum(char c);//判断一个字符是否为数字0-9，是返回1，否返回0
bool isOpt(char c);//判断一个字符是否为操作符，是返回1，否返回0
bool isPair(char lc, char rc);//判断lc,lr是否匹配，是返回1，否返回0，匹配对为()或[]或{}
double str_to_num(char *s);//将字符串转化为double类型值
int PriorityTable(char c);//创建操作符优先级表
double compute(double a1, double a2, char opt);//进行四则运算，传入两个操作数，一个操作符，得到运算结果double

#endif // MY_EXPRESSION_H
