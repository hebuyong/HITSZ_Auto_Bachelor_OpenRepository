#include <windows.h>
#include<iostream>
#include<math.h>
#include<string>
#define length 100
using namespace std;
const char g_szClassName[] = "myWindowClass";
int x,y,key;
int draw;
int p=0;
double ans=0;
char com[length];
int position=-1;
template<class type>
class stack
{
public:
    stack(type a)
    {
        for (int i = 0; i < length; i++)
            link[i] = a;
    }
    type link[length];
};
class cal_class
{
public:
    string command;
    double num[length] ;
    int brackets[length] ; //1-{,2-[,3-(,4-},5-],6-)
    cal_class(char com[]){reset();command = com;}
    double CALCULATE();
private:
    void reset();
    int former(int i);
    int later(int i, int j);
    void spl();
    double calcualte_simple(int n, double a, double b);
    double calcualte_result();
    double calcualte();
};
void cal_class::reset()
{
    for (int i = 0; i < length; i++)
    {
        command = "";
        num[i] = 0;//num，brackets默认初值为0,'0'
        brackets[i] = 0;
    }
}
int cal_class::former(int i)
{
    int j;
    for (j = i + 1; j < int(command.size()) && j < length; j++)
    {
        if (int(command[j]) >= 48 && int(command[j]) <= 57)
            num[i] = num[i] * 10 + command[j] - '0';
        else
            break;
    }
    return j;
}
int cal_class::later(int i, int j)
{
    if (int(command[j]) == 46)
    {
        if (!(command[j + 1] >= 48 && command[j + 1] <= 57))
            return 0;
        else
        {
            for (int k = j + 1; k < int(command.size()) && k < length; k++)
            {
                if (int(command[k]) >= 48 && int(command[k]) <= 57)
                {
                    num[i] = num[i] + (command[k] - '0') / double(pow(10, k - j));
                    //最后为数字结尾
                    if (k == int(command.size()) - 1) return command.size() - 1;
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
void cal_class::spl()
{
    for (int i = 0; i < int(command.size()) && i < length; i++)
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
    for (int i = 0; i < int(command.size()) && i < length; i++)
    {
        int j, k;
        if (int(command[i]) >= 48 && int(command[i]) <= 57)
        {
            num[i] = command[i] - '0';
            j = former(i);
            k = later(i, j);
            if (k != 0){i = k;}
            else{i = j;cout << "wrong\n";}
        }
    }
}
double cal_class::calcualte_simple(int n, double a, double b)
{
    if (n == 7)return a + b;
    if (n == 8)return a - b;
    if (n == 9)return a * b;
    if (n == 10 && b != 0)return a / b;
    return 0;
}
double cal_class::calcualte_result()
{
    int order[11] = { 0,3,0,3,0,3,0,1,1,2,2 };//加减乘除7,8,9,10
    double result = 999.99;
    //操作符栈
    stack <int> oper(0);
    int position_oper = 0;
    //操作数栈
    stack <double> number(0);
    int position_number = 0;
    for (int i = 0; i < int(command.size()) && i < length; i++)
    {
        if (num[i] != 0)//数值数组非0存入
        {
            number.link[position_number + 1] = num[i];
            position_number++;
        }
        if (brackets[i] != 0 && brackets[i] != 11)//操作符数组非0且非.存入
        {
            if (order[oper.link[position_oper]] < order[brackets[i]] || order[oper.link[position_oper]] == 3)//优先级高于现栈顶优先级，压入
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
                        if (oper.link[position_oper] == brackets[i] - 1)
                        {
                            position_oper--;
                            break;
                        }
                        else
                        {
                            number.link[position_number - 1] = calcualte_simple(oper.link[position_oper], \
                                                               number.link[position_number - 1], number.link[position_number]);
                            position_number--;
                            position_oper--;
                        }
                    }
                }
                else
                {
                    if (position_number > 1)
                    {
                        if (position_oper > 0)
                        {
                            number.link[position_number - 1] = calcualte_simple(oper.link[position_oper], \
                                                               number.link[position_number - 1], number.link[position_number]);
                            position_number--;
                            position_oper--;
                        }
                    }
                    oper.link[position_oper + 1] = brackets[i];
                    position_oper++;
                }
            }
        }
    }
    if (oper.link[position_oper] == 9 || oper.link[position_oper] == 10)
    {
        number.link[position_number - 1] = calcualte_simple(oper.link[position_oper], \
                                           number.link[position_number - 1], number.link[position_number]);
        position_number--;
        position_oper--;
    }
    for (int i = 1; i <= position_oper; i++)
    {
        number.link[i + 1] = calcualte_simple(oper.link[i], \
                                              number.link[i], number.link[i + 1]);
    }
    result = number.link[position_number];
    return result;
}
double cal_class::calcualte()
{
    int wrong = 0;
    //left从第二个存储位置开始存
    stack <int> left('0');
    int position = -1;
    //判断括号是否匹配
    for (int i = 0; i < int(command.size()) && i < length; i++)
    {
        if (brackets[i] == 1 || brackets[i] == 3 || brackets[i] == 5)
        {
            left.link[position + 1] = brackets[i];
            position++;
        }
        if (brackets[i] == 2 || brackets[i] == 4 || brackets[i] == 6)
        {
            if (position == -1){wrong = i;break;}
            if (brackets[i] == 2)
            {
                if (left.link[position] != 1){wrong = i;break;}
                else{left.link[position] = 0;position--;}
            }
            if (brackets[i] == 4)
            {
                if (left.link[position] != 3){wrong = i;break;}
                else{left.link[position] = 0;position--;}
            }
            if (brackets[i] == 6)
            {
                if (left.link[position] != 5){wrong = i;break;}
                else{left.link[position] = 0;position--;}
            }
        }
    }
    if (wrong != 0){return 999.99;cout << "wrong" << endl;}
    else
    {
        if (position == -1)//正确，输出计算结果
        {
            double result = calcualte_result();
            if (result == 999.99){return 999.99;cout << "wrong" << endl;}
            else return result;
        }
        else{return 999.99;cout << "wrong" << endl;}
    }
}
double cal_class:: CALCULATE(){spl();return calcualte();}
void Text(HDC hdc)
{
    //字体设置大小，颜色
    HFONT hFont = CreateFont(60, 0, 0, 0, FW_DONTCARE, 0, 0, 0, GB2312_CHARSET,
                             OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                             DEFAULT_PITCH|FF_DONTCARE, "微软雅黑");//创建字体
    SelectObject(hdc, hFont);//选择字体
    SetBkMode(hdc, TRANSPARENT);
    char c[128];
    static int ind=10;
    int len=sprintf(c,"%d",ind);
    //绘制默认书写按钮文字
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            ind=3*j+i+1;
            len=sprintf(c,"%d",ind);
            TextOut(hdc,40+i*100, 320-j*100,TEXT(c),len);
        }
    }
    TextOut(hdc,40,420,TEXT("."),1);
    TextOut(hdc,140,420,TEXT("0"),1);
    TextOut(hdc,240,420,TEXT("="),1);
    TextOut(hdc,340,120,TEXT("+"),1);
    TextOut(hdc,340,220,TEXT("-"),1);
    TextOut(hdc,340,320,TEXT("*"),1);
    TextOut(hdc,340,420,TEXT("/"),1);
    TextOut(hdc,440,220,TEXT("B"),1);
    TextOut(hdc,440,420,TEXT(")"),1);
    TextOut(hdc,440,320,TEXT("("),1);
    TextOut(hdc,440,120,TEXT("C"),1);
}
// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_CLOSE:
        cout<<" WM_CLOSE"<<endl;
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        cout<<" WM_DESTROY"<<endl;
        PostQuitMessage(0);
        break;
    case WM_CREATE:
        cout<<" WM_CREATE"<<endl;
        SetTimer(hwnd,1,100,NULL);
        draw=1;
        break;
    case WM_MOVE:
        x=LOWORD(lParam);
        y=HIWORD(lParam);
        cout<<" WM_MOVING at "<<x<<" "<<y<<endl;
        break;
    case WM_SIZE:
        cout<<" WM_SIZE"<<endl;
        break;
    case WM_LBUTTONDOWN:
        x=LOWORD(lParam);
        y=HIWORD(lParam);
        cout<<" WM_LBUTTONDOWN at "<<x<<" "<<y<<endl;
        p=1;
        //输入表达字符
        {
            for(int i=0; i<5; i++)
            {
                for(int j=0; j<4; j++)
                {
                    if(x>=5+i*100&&x<=95+i*100)
                    {
                        if(y>=105+j*100&&y<=195+j*100)
                        {
                            //1---9
                            if(i<=2&&j<=2)
                            {
                                char temp[2];
                                if(j==0)
                                    snprintf(temp, sizeof(temp), "%d", 3*j+i+1+6);
                                if(j==2)
                                    snprintf(temp, sizeof(temp), "%d", 3*j+i+1-6);
                                if(j==1)
                                    snprintf(temp, sizeof(temp), "%d", 3*j+i+1);
                                com[++position]=temp[0];
                            }
                            //第四排
                            if(j==3)
                            {
                                if(i==0)
                                    com[++position]='.';
                                if(i==1)
                                    com[++position]='0';
                                if(i==2)
                                {
                                    com[++position]='=';
                                    cal_class a(com);
                                    ans=a.CALCULATE();
                                    for(int i=0; i<length; i++)
                                        com[i]='0';
                                    position=-1;
                                }
                                if(i==3)
                                    com[++position]='/';
                                if(i==4)
                                    com[++position]=')';
                            }
                            //第四列
                            if(i==3)
                            {
                                if(j==0)
                                    com[++position]='+';
                                if(j==1)
                                    com[++position]='-';
                                if(j==2)
                                    com[++position]='*';
                            }
                            //第五列
                            if(i==4)
                            {
                                if(j==0)
                                {
                                    position=-1;
                                    ans=0;
                                    break;
                                }
                                if(j==1)
                                {
                                    position--;
                                    break;
                                }
                                if(j==2)
                                    com[++position]='(';
                            }

                        }
                    }
                }
            }

        }

        break;
    case WM_LBUTTONUP:
        x=LOWORD(lParam);
        y=HIWORD(lParam);
        cout<<" WM_LBUTTONUP at "<<x<<" "<<y<<endl;
        p=0;
        break;
    case WM_MOUSEMOVE:
        cout<<" WM_MOUSEMOVE "<<endl;
        x=LOWORD(lParam);
        y=HIWORD(lParam);
        cout<<" WM_MOUSEMOVE at "<<x<<" "<<y<<endl;
        break;
    case WM_RBUTTONDOWN:
        x=LOWORD(lParam);
        y=HIWORD(lParam);
        cout<<" WM_RBUTTONDOWN at "<<x<<" "<<y<<endl;
        break;
    case WM_KEYDOWN:
        key=wParam;
        if((key>=48&&key<=57)||key==88||key==191||key==187||key==219||key==221)
        {
            if(key>=48&&key<=57)
                com[++position]=key-48+'0';
            if(key==88)
                com[++position]='*';
            if(key==191)
                com[++position]='/';
            if(key==187)
            {
                com[++position]='=';
                cal_class a(com);
                ans=a.CALCULATE();
                for(int i=0; i<length; i++)
                    com[i]='0';
                position=-1;
            }
            if(key==219)
                com[++position]='(';
            if(key==221)
                com[++position]=')';
        }
        cout<<" WM_KEYDOWN : "<<key<<endl;
        break;
    case WM_KEYUP:
        key=wParam;
        cout<<" WM_KEYUP : "<<key<<endl;
        break;
    case WM_TIMER:
        cout<<" WM_TIMER"<<endl;
        if(draw)
        {
            HDC hdc=GetDC(hwnd);
            HBRUSH hBrush;
            RECT rect;
            //背景白色的最大矩形框
            hBrush = CreateSolidBrush(RGB(255,255,255));
            SetRect(&rect, 0, 0,500,500);
            FillRect(hdc, &rect, hBrush);
            //绘制默认输入显示区域以及按钮区域
            hBrush = CreateSolidBrush(RGB(220,220,220));
            SetRect(&rect, 5,5,495,95);
            FillRect(hdc, &rect, hBrush);
            for(int i=0; i<5; i++)
            {
                for(int j=0; j<4; j++)
                {
                    SetRect(&rect, 5+i*100, 105+j*100,95+i*100,195+j*100);
                    FillRect(hdc, &rect, hBrush);
                }
            }
            //鼠标在上方
            hBrush = CreateSolidBrush(RGB(180,180,180));
            for(int i=0; i<5; i++)
            {
                for(int j=0; j<4; j++)
                {
                    if(x>=5+i*100&&x<=95+i*100)
                    {
                        if(y>=105+j*100&&y<=195+j*100)
                        {
                            SetRect(&rect, 5+i*100, 105+j*100,95+i*100,195+j*100);
                            FillRect(hdc, &rect, hBrush);
                        }
                    }
                }
            }
            //左键down
            if(p==1)
            {
                //按下绘制加深矩形
                {
                    HDC hdc=GetDC(hwnd);
                    HBRUSH hBrush;
                    RECT rect;
                    hBrush = CreateSolidBrush(RGB(140,140,140));
                    for(int i=0; i<5; i++)
                    {
                        for(int j=0; j<4; j++)
                        {

                            if(x>=5+i*100&&x<=95+i*100)
                            {
                                if(y>=105+j*100&&y<=195+j*100)
                                {

                                    SetRect(&rect, 5+i*100, 105+j*100,95+i*100,195+j*100);
                                    FillRect(hdc, &rect, hBrush);
                                }
                            }
                        }
                    }
                    Text(hdc);
                    Sleep(50);
                }
            }
            Text(hdc);
            {
                //字体设置大小，颜色
                HFONT hFont = CreateFont(40, 0, 0, 0, FW_DONTCARE, 0, 0, 0, GB2312_CHARSET,
                                         OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                         DEFAULT_PITCH|FF_DONTCARE, "微软雅黑");//创建字体
                SelectObject(hdc, hFont);//选择字体
                SetBkMode(hdc, TRANSPARENT);

                if(position==-1)
                {
                    string a=to_string(ans);
                    char b[30];
                    for(int i=0; i<int(a.size()); i++)
                        b[i]=a[i];
                    for(int i=int(a.size()); i>=0; i--)
                    {
                        char c[2];
                        c[0]=b[i];
                        TextOut(hdc,480+(i-int(a.size()))*20,30,c,1);
                    }
                }
                else
                {
                    char str[30];
                    for(int i=position; i>=0; i--)
                    {
                        str[0]=com[i];
                        TextOut(hdc,460+(i-position)*20,30,TEXT(str),1);
                    }
                }
            }
            hBrush = NULL;
            ReleaseDC(hwnd,hdc);
        }
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;
    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
               WS_EX_CLIENTEDGE,
               g_szClassName,
               "Simple calculator",
               WS_OVERLAPPEDWINDOW,
               CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
               NULL, NULL, hInstance, NULL);
    SetWindowPos(hwnd,HWND_NOTOPMOST,500,100,520,545,SWP_SHOWWINDOW );
    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
