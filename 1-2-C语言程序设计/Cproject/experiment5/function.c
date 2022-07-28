#include <stdio.h>
#include <stdlib.h>
#include "function.h"

void PrintfChoice()/*打印提示*/
{
    printf("===========================\n");
    printf("1.Input record\n2.Calculate average salary\n3.Sort in descending order by salary\n4.Search by ID\n5.List record\n6.Exit\n");
    printf("===========================\n");
    printf("Please input your choice:");
}
void InputDate(int num,int list[],double salary[])/*输入数据*/
{
    int i,ret;
    printf("Please input employee ID and salary(01,5000):\n");
    for(i=0; i<=num-1; i++)
    {
        ret=scanf("%d,%lf",&list[i],&salary[i]);
        while(ret!=2||salary[i]<5000-1e-5||salary[i]>20000+1e-5)
        {
            printf("Please input salary between 5000 and 20000:\n");
            while(getchar()!='\n');
            ret=scanf("%d,%lf",&list[i],&salary[i]);
        }
    }
}
double Average(int num,double a[])/*求平均值*/
{
    int i;
    double sum=0;
    for(i=0; i<=num-1; i++)
    {
        sum+=a[i];
    }
    return sum/num;
}
void Order(int num,int a[],double b[])/*排序*/
{
    int listmax,tem,i,j;
    double salarytem;
    for(i=0; i<=num-2; i++)
    {
        listmax=i;
        for(j=i+1; j<=num-1; j++)
        {
            if(b[j]>b[listmax])
            {
                listmax=j;
            }

        }
        if(listmax!=i)
        {
            tem=a[i];
            a[i]=a[listmax];
            a[listmax]=tem;
            salarytem=b[i];
            b[i]=b[listmax];
            b[listmax]=salarytem;
        }

    }
}
int Search(int num,int b[])/*搜索查找*/
{
    int que,i;
    printf("SEARCH:Please input employee ID.\n");
    scanf("%d",&que);
    for(i=0; i<=num-1; i++)
    {
        if(que==b[i])
        {
            return i;
        }
    }
    return -1;

}
