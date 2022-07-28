#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
#define MAX_EMPLOYEE 30
#define MAX_NAMELINE 21


void PrintfChoice()/**打印提示**/
{
    printf("=================================================\n");
    printf("01.Input record\n02.delete record(by employee ID)\n03.search by name\n04.Search by ID\n05.Search by hire date\n"
           "06.Modify record\n07.Statistic\n08.Sort record in descending by ID\n09.Sort record in descending by name\n"
           "10.Sort record in descending by hire date\n11.List record\n0.Exit\n");
    printf("=================================================\n");
    printf("Please input your choice:");
}

int  Getemployee_num()/**得到文件内成员个数**/
{
    int result;
    FILE *fp=NULL;
    if((fp=fopen("staff.txt","r"))!=NULL)
    {
        fseek(fp,0,2);
        result=ftell(fp)/sizeof(EMPLOY);
    }
    else
    {
        printf("FAIL TO OPEN FILE OR NOT EXIST!\n");
        fp=fopen("staff.txt","w");
        result=0;

    }
    while((fclose(fp))!=0)
    {
        printf("FAIL TO CLOSE FILE!\n");
        exit(1);
    }
    return result;
}

void Inputdate(int num,EMPLOY emp[])/**输入数据**/
{
    int i,ret,run,wrong=0;
    for(i=0; i<=num-1; i++)
    {
        while(getchar()!='\n');
        printf("Please input employee name.(max=20)\n");
        gets(emp[i].name);
        printf("Please input employee's ID, hiredate(year,month,day) and salary:\n");
        ret=scanf("%d,%d,%d,%d,%f",&emp[i].ID,&emp[i].hiredate.year,&emp[i].hiredate.month,&emp[i].hiredate.day,&emp[i].salary);
        while(ret!=5||emp[i].salary<5000-1e-5||emp[i].salary>20000+1e-5)
        {
            printf("Please input salary between 5000 and 20000:\n");
            while(getchar()!='\n');
            printf("Please input employee name.(max=20)\n");
            gets(emp[i].name);
            printf("Please input employee ID hiredate(year,month,day) and salary:\n");
            ret=scanf("%d,%d,%d,%d,%f",&emp[i].ID,&emp[i].hiredate.year,&emp[i].hiredate.month,&emp[i].hiredate.day,&emp[i].salary);
        }
        if(emp[i].hiredate.year%4!=0)
        {
            run=0;
        }
        else
        {
            if(emp[i].hiredate.year%100==0)
            {
                if(emp[i].hiredate.year%400==0)
                {
                    run=1;
                }
                else run=0;
            }
            else run=1;
        }
        while(ret!=5||emp[i].hiredate.month<1||emp[i].hiredate.month>12||emp[i].hiredate.day<1||emp[i].hiredate.day>28)
        {
            wrong=0;
            if(ret!=5||emp[i].hiredate.month<1||emp[i].hiredate.month>12)
            {
                wrong=1;

            }
            if(emp[i].hiredate.month==1||emp[i].hiredate.month==3||emp[i].hiredate.month==5||emp[i].hiredate.month==7||emp[i].hiredate.month==8||emp[i].hiredate.month==10||emp[i].hiredate.month==12)
            {
                if(emp[i].hiredate.day<1||emp[i].hiredate.day>31)
                {
                    wrong=1;

                }
            }
            if(emp[i].hiredate.month==4||emp[i].hiredate.month==6||emp[i].hiredate.month==9||emp[i].hiredate.month==11)
            {
                if(emp[i].hiredate.day<1||emp[i].hiredate.day>30)
                {
                    wrong=1;

                }
            }
            if(emp[i].hiredate.month==2)
            {
                if(run==1)
                {
                    if(emp[i].hiredate.day<1||emp[i].hiredate.day>29)
                    {
                        wrong=1;

                    }

                }
                else
                {
                    if(emp[i].hiredate.day<1||emp[i].hiredate.day>28)
                    {
                        wrong=1;
                    }
                }
            }
            if(wrong==1)
            {
                printf("WRONG HIREDATE!\n");
                while(getchar()!='\n');
                printf("Please input employee name.(max=20)\n");
                gets(emp[i].name);
                printf("Please input employee ID hiredate(year,month,day) and salary:\n");
                ret=scanf("%d,%d,%d,%d,%f",&emp[i].ID,&emp[i].hiredate.year,&emp[i].hiredate.month,&emp[i].hiredate.day,&emp[i].salary);
                if(emp[i].hiredate.year%4!=0)
                {
                    run=0;
                }
                else
                {
                    if(emp[i].hiredate.year%100==0)
                    {
                        if(emp[i].hiredate.year%400==0)
                        {
                            run=1;
                        }
                        else run=0;
                    }
                    else run=1;
                }
            }
            if(wrong==0)
            {
                break;
            }
        }
        printf("%-10s,%d,%d/%02d/%02d,%.2f\n",emp[i].name,emp[i].ID,emp[i].hiredate.year,emp[i].hiredate.month,emp[i].hiredate.day,emp[i].salary);
    }

}

void Addinfile(int num,EMPLOY emp[])/**将结构体数组添加文件内**/
{
    FILE *fp=NULL;
    if((fp=fopen("staff.txt","a"))!=NULL)
    {
        fwrite(emp,sizeof(EMPLOY),num,fp);
    }
    else
    {
        printf("FAIL TO OPEN FILE!\n");
        exit(1);

    }
    while((fclose(fp))!=0)
    {
        printf("FAIL TO CLOSE FILE!\n");
        exit(1);
    }
}
void Copyinfile(int num,EMPLOY emp[])/**将结构体数组复制到文件内**/
{
    FILE *fp=NULL;
    if((fp=fopen("staff.txt","w"))!=NULL)
    {
        fwrite(emp,sizeof(EMPLOY),num,fp);
    }
    else
    {
        printf("FAIL TO OPEN FILE!\n");
        exit(1);

    }
    while((fclose(fp))!=0)
    {
        printf("FAIL TO CLOSE FILE!\n");
        exit(1);
    }
}

void Copyoutfile(int num,EMPLOY emp[])/**将文件内容拷到结构体数组内**/
{
    FILE *fp=NULL;
    if((fp=fopen("staff.txt","r"))!=NULL)
    {
        fread(emp,sizeof(EMPLOY),num,fp);
    }
    else
    {
        printf("FAIL TO OPEN FILE!\n");
        exit(1);

    }
    while((fclose(fp))!=0)
    {
        printf("FAIL TO CLOSE FILE!\n");
        exit(1);
    }
}

int Deletedate(int n,int num,EMPLOY emp[])/**删除文件**/
{
    emp[n].ID=0;
    OrderbyID(num,emp);
    return 0;
}

void OrderbyID(int num,struct Employ emp[])/**ID排序**/
{
    int listmax,i,j;
    EMPLOY temp;
    for(i=0; i<=num-2; i++)
    {
        listmax=i;
        for(j=i+1; j<=num-1; j++)
        {
            if(emp[j].ID>emp[listmax].ID)
            {
                listmax=j;
            }
        }
        if(listmax!=i)
        {
            temp=emp[i];
            emp[i]=emp[listmax];
            emp[listmax]=temp;
        }
    }
}
void Orderbyname(int num,struct Employ emp[])/**姓名排序**/
{
    int listmax,i,j;
    EMPLOY temp;
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
            temp=emp[i];
            emp[i]=emp[listmax];
            emp[listmax]=temp;
        }
    }
}

void Orderbyhiredate(int num,EMPLOY emp[])/**入职日期排序**/
{
    int listmax,i,j;
    EMPLOY temp;
    for(i=0; i<=num-2; i++)
    {
        listmax=i;
        for(j=i+1; j<=num-1; j++)
        {
            if(emp[j].hiredate.year>emp[listmax].hiredate.year)
            {
                listmax=j;
            }
        }
        if(listmax!=i)
        {
            temp=emp[i];
            emp[i]=emp[listmax];
            emp[listmax]=temp;
        }
    }
    for(i=0; i<=num-2; i++)
    {
        listmax=i;
        for(j=i+1; j<=num-1; j++)
        {
            if(emp[j].hiredate.year==emp[listmax].hiredate.year)
            {
                if(emp[j].hiredate.month>emp[listmax].hiredate.month)
                {
                    listmax=j;
                }
            }
        }
        if(listmax!=i)
        {
            temp=emp[i];
            emp[i]=emp[listmax];
            emp[listmax]=temp;
        }
    }
    for(i=0; i<=num-2; i++)
    {
        listmax=i;
        for(j=i+1; j<=num-1; j++)
        {
            if(emp[j].hiredate.year==emp[listmax].hiredate.year)
            {
                if(emp[j].hiredate.month==emp[listmax].hiredate.month)
                {
                    if(emp[j].hiredate.day>emp[listmax].hiredate.day)
                    {
                        listmax=j;
                    }
                }
            }
        }
        if(listmax!=i)
        {
            temp=emp[i];
            emp[i]=emp[listmax];
            emp[listmax]=temp;
        }
    }
}

int Searchbyname(int num,struct Employ emp[])/**以员工名字查找**/
{
    int i;
    char que[MAX_NAMELINE];
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
    int que,i,ret;
    while(getchar()!='\n');
    ret=scanf("%d",&que);
    while(ret!=1)
    {
        printf("Please input proper employee ID.\n");
        while(getchar()!='\n');
        ret=scanf("%d",&que);
    }
    for(i=0; i<=num-1; i++)
    {
        if(que==emp[i].ID)
        {
            return i;
        }
    }
    return -1;

}

int Searchbyhiredate(int num,EMPLOY emp[])/**以入职日期查找**/
{
    int que1,que2,que3,i,ret;
    while(getchar()!='\n');
    ret=scanf("%d,%d,%d",&que1,&que2,&que3);
    while(ret!=3)
    {
        printf("Please input proper employee hiredate.\n");
        while(getchar()!='\n');
        ret=scanf("%d,%d,%d",&que1,&que2,&que3);
    }
    for(i=0; i<=num-1; i++)
    {
        if(que1==emp[i].hiredate.year)
        {
            if(que2==emp[i].hiredate.month)
            {
                if(que3==emp[i].hiredate.day)
                {
                    return i;
                }
            }
        }
    }
    return -1;
}

void Modify(int num,EMPLOY emp[])/**修改员工工资**/
{
    int ans,ret;
    float s;
    printf("Please input employee ID:");
    ans=SearchbyID(num,emp);
    while(ans==-1)
    {
        printf("NO FOUND! Please input employee ID again:");
        ans=SearchbyID(num,emp);
    }
    printf("The orignal salary is %.2f  Please input modified salary:",emp[ans].salary);
    while(getchar()!='\n');
    ret=scanf("%f",&s);
    while(ret!=1||s<5000-1e-5||s>20000+1e-5)
    {
        printf("Please input salary between 5000 and 20000:");
        while(getchar()!='\n');
        ret=scanf("%f",&s);
    }
    emp[ans].salary=s;
    printf("MODIFIED SUCCESSFULLY!\n");
}

float Sum(int num,EMPLOY emp[])/**求和工资**/
{
    int i;
    float sum=0;
    for (i=0; i<=num-1; i++)
    {
        sum+=emp[i].salary;
    }
    return sum;
}

void Inputstatis(STATIS sta)/**将统计数据复制到文件内**/
{
    FILE *fp=NULL;
    if((fp=fopen("staff_statis.txt","w"))!=NULL)
    {
        fwrite(&sta,sizeof(STATIS),1,fp);
    }
    else
    {
        printf("FAIL TO OPEN FILE!\n");
        exit(1);

    }
    while((fclose(fp))!=0)
    {
        printf("FAIL TO CLOSE FILE!\n");
        exit(1);
    }
}
