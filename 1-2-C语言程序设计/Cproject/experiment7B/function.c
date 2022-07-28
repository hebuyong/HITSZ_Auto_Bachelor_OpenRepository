#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
#define MAX_EMPLOYEE 30
#define MAX_NAMELINE 21


void PrintfChoice()/**打印提示**/
{
    printf("===========================\n");
    printf("1.Input record\n2.Sort in descending ordered by salary\n3.Sort by name\n4.search by name\n5.Search by ID\n6.List record\n0.Exit\n");
    printf("===========================\n");
    printf("Please input your choice:");
}
void InputDate(int num,struct Employ emp[])/**输入数据**/
{
    int i,ret;
    for(i=0; i<=num-1; i++)
    {
        while(getchar()!='\n');
        printf("Please input employee name.(max=20)\n");
        gets(employee[i].name);
        printf("Please input employee ID and salary(01,5000):\n");
        ret=scanf("%d,%f",&employee[i].ID,&employee[i].salary);
        while(ret!=2||employee[i].salary<5000-1e-5||employee[i].salary>20000+1e-5)
        {
            printf("Please input salary between 5000 and 20000:\n");
            while(getchar()!='\n');
            printf("Please input employee name.(max=20)\n");
            gets(employee[i].name);
            printf("Please input employee ID and salary(01,5000):\n");
            ret=scanf("%d,%f",&employee[i].ID,&employee[i].salary);
        }
    }
}
void Orderbysalary(int num,struct Employ emp[])/**薪资排序**/
{
    printf("Sort in descending ordered by salary.\n");
    int listmax,idtemp,i,j;
    float salarytemp;
    char nametemp[MAX_NAMELINE];
    for(i=0; i<=num-2; i++)
    {
        listmax=i;
        for(j=i+1; j<=num-1; j++)
        {
            if(emp[j].salary>emp[listmax].salary)
            {
                listmax=j;
            }

        }
        if(listmax!=i)
        {
            idtemp=emp[i].ID;
            emp[i].ID=emp[listmax].ID;
            emp[listmax].ID=idtemp;

            salarytemp=emp[i].salary;
            emp[i].salary=emp[listmax].salary;
            emp[listmax].salary=salarytemp;

            strcpy(nametemp,emp[i].name);
            strcpy(emp[i].name,emp[listmax].name);
            strcpy(emp[listmax].name,nametemp);

        }

    }
}
void Orderbyname(int num,struct Employ emp[])/**姓名排序**/
{
    printf("Sort by name.\n");
    int listmax,idtemp,i,j;
    float salarytemp;
    char nametemp[MAX_NAMELINE];
    for(i=0; i<=num-2; i++)
    {
        listmax=i;
        for(j=i+1; j<=num-1; j++)
        {
            if(strcmp(emp[j].name,emp[listmax].name)<0)
            {
                listmax=j;
            }

        }
        if(listmax!=i)
        {
            idtemp=emp[i].ID;
            emp[i].ID=emp[listmax].ID;
            emp[listmax].ID=idtemp;

            salarytemp=emp[i].salary;
            emp[i].salary=emp[listmax].salary;
            emp[listmax].salary=salarytemp;

            strcpy(nametemp,emp[i].name);
            strcpy(emp[i].name,emp[listmax].name);
            strcpy(emp[listmax].name,nametemp);

        }

    }

}
int Searchbyname(int num,struct Employ emp[])/**以员工名字查找**/
{
    int i;
    char que[MAX_NAMELINE];
    printf("SEARCH:Please input employee's name.\n");
    while(getchar()!='\n');
    gets(que);
    for(i=0; i<=num-1; i++)
    {
        if(strcmp(que,emp[i].name)==0)
        {
            return i;
        }
    }
    return -1;
}
int SearchbyID(int num,struct Employ emp[])/**以员工号搜索查找**/
{
    int que,i;
    printf("SEARCH:Please input employee ID.\n");
    while(getchar()!='\n');
    scanf("%d",&que);
    for(i=0; i<=num-1; i++)
    {
        if(que==emp[i].ID)
        {
            return i;
        }
    }
    return -1;

}

