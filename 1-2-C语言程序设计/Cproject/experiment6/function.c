#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
#define MAX_EMPLOYEE 30



void PrintfChoice()/**打印提示**/
{
    printf("===========================\n");
    printf("1.Input record\n2.Sort in descending order by salary\n3.search by name\n4.Search by ID\n5.List record\n0.Exit\n");
    printf("===========================\n");
    printf("Please input your choice:");
}
void InputDate(int num,char name[],int idsalary[][2])/**输入数据**/
{
    int i,ret;
    printf("Please input employee name ID and salary(01,5000):\n");
    for(i=0; i<=num-1; i++)
    {
        while(getchar()!='\n');
        ret=scanf("%c,%d,%d",&name[i],&idsalary[i][0],&idsalary[i][1]);
        while(ret!=3||idsalary[i][1]<5000-1e-5||idsalary[i][1]>20000+1e-5)
        {
            printf("Please input salary between 5000 and 20000:\n");
            while(getchar()!='\n');
            ret=scanf("%c,%d,%d",&name[i],&idsalary[i][0],&idsalary[i][1]);
        }
    }
}
void Order(int num,char name[],int a[][2])/**排序**/
{
    int listmax,idtemp,i,j;
    int salarytemp;
    char nametemp;
    for(i=0; i<=num-2; i++)
    {
        listmax=i;
        for(j=i+1; j<=num-1; j++)
        {
            if(a[j][1]>a[listmax][1])
            {
                listmax=j;
            }

        }
        if(listmax!=i)
        {
            idtemp=a[i][0];
            a[i][0]=a[listmax][0];
            a[listmax][0]=idtemp;
            salarytemp=a[i][1];
            a[i][1]=a[listmax][1];
            a[listmax][1]=salarytemp;
            nametemp=name[i];
            name[i]=name[listmax];
            name[listmax]=nametemp;
        }

    }
}
int Searchbyname(int num,char name[])/**以员工名字查找**/
{
    int i;
    char que;
    printf("SEARCH:Please input employee's name.\n");
    while(getchar()!='\n');
    que=getchar();
    for(i=0; i<=num-1; i++)
    {
        if(que==name[i])
        {
            return i;
        }
    }
    return -1;
}

int SearchbyID(int num,int a[][2])/**以员工号搜索查找**/
{
    int que,i;
    printf("SEARCH:Please input employee ID.\n");
    while(getchar()!='\n');
    scanf("%d",&que);
    for(i=0; i<=num-1; i++)
    {
        if(que==a[i][0])
        {
            return i;
        }
    }
    return -1;

}
