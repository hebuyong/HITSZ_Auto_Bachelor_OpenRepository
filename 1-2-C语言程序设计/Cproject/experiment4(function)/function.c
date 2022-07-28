#include "function.h"

int Whether_primer(int a)
{
    int ans=0,i;
    if(a==1)
        ans=2;
    if(a==2)
        ans=1;

    if(a>2)
    {
        i=2;
        do
        {
            if(a%i==0)
            {
                ans=1;
                break;
            }
            i++;
        }while(i<=a-1);
    }
    return ans;
}

int Get_factor(int number)
{
    int i,j,num;
    num=number;
    printf("%d=1",number);
    for(i=2; i<=number-1; i++)
    {
        for(j=i;;)//对同一个因子多重分解
        {
            if(num%j==0)
            {
                printf("*%d",j);
                num=num/j;
            }
            else
                break;
        }
    }
    printf("\n");
}
