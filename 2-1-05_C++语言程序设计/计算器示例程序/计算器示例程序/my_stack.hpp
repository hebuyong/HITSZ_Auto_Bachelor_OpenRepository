#ifndef MY_STACK_HPP_INCLUDED
#define MY_STACK_HPP_INCLUDED

#include <stdlib.h>
using namespace std;

//栈又名堆栈，它是一种运算受限的线性表。限定在仅在表尾进行插入和删除操作的线性表。
//向一个栈插入新元素又称为进栈、入栈或压栈，它是把新元素放到栈顶元素的上面，使之成为新的栈顶元素；
//从一个栈三处元素又称为出栈或退栈，它是把栈顶元素删除掉，使其相邻的元素成为新的栈顶元素。

template<class T>
class MyStack
{
    public:
        //构造函数
        MyStack()
        {
            maxsize =1;
            data = new T[maxsize];//动态创建存储空间
            top = -1;//top为-1标识空栈
        }
        //析构函数
        virtual ~MyStack()
        {
            if(data != NULL)
            {
                delete[] data;//释放内存
                data = NULL;
            }
        }
        //判断是否为空栈，空栈返回1，非空返回0
        bool isEmpty()
        {
            return top==-1;
        }
        //获取栈顶元素
        T getTop()
        {
            return data[top];
        }
        //出栈，返回栈顶元素，其相邻元素成为新的栈顶元素
        T pop()
        {
            return data[top--];
        }
        //入栈，将新的元素放入栈顶元素上方
        void push(T x)
        {
            if(top+1 == maxsize)
                expand();

            data[++top]=x;
        }

    private:
        T *data;
        int maxsize;
        int top;
        //若栈空间不足，将其扩大两倍
        void expand()
        {
 			T* temp = data;
            data = new T[maxsize*2];
            for(int i=0; i<=top; i++)
                data[i] = temp[i];
            delete[] temp;
			temp = NULL;
            maxsize = maxsize*2;
        }
	protected:

};


#endif // MY_STACK_HPP_INCLUDED
