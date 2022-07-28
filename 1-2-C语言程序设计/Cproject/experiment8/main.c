#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

/**************************
**员工姓名、员工号、工资
数据输入，排序，查找系统V3.0
**************************/
#define MAX_EMPLOYEE 30
#define MAX_NAMELINE 21
int main()
{
    printf("Number:190410102\nsubject No.8-program No.1\n\n");

    /**choice用于用户选择，ret用于判断数据输入正误,
    ans_search用于接收搜索结果，count用于记录是否输入数据,
    employ用于记录姓名、员工号、薪资**/
    int choice,ret,i,ans_search,num_employee=0,addnum;
    EMPLOY employee[MAX_EMPLOYEE];
    STATIS sta;
    for(i=1; i<=MAX_EMPLOYEE-1; i++)
    {
        employee[i].ID=0;
    }
    num_employee=Getemployee_num();
    printf("There has/have been %d employee data in file.\n",num_employee);
    Copyoutfile(num_employee,employee);

    /**系统循环使用**/
    for(;;)
    {
        PrintfChoice();
        /**输入用户选择并进行准确性检查**/
        ret=scanf("%d",&choice);
        while(ret!=1||choice<0||choice>11)
        {
            printf("Please input choice(0<=n<=11):");
            while(getchar()!='\n');
            ret=scanf("%d",&choice);
        }
        if(choice==1)/**输入数据并录入文件**/
        {
            /**输入员工数并进行正确性检查**/
            printf("Please input how many employee's do you want to add in(1<=n<=%d):",30-num_employee);
            ret=scanf("%d",&addnum);
            while(ret!=1||addnum<0||addnum>30-num_employee)
            {
                printf("Please input number(0<=n<=%d):",30-num_employee);
                while(getchar()!='\n');
                ret=scanf("%d",&addnum);
            }
            num_employee+=addnum;
            Inputdate(addnum,employee);
            Addinfile(addnum,employee);
            Copyoutfile(num_employee,employee);
        }
        if(choice==2)/**根据员工号删除数据**/
        {
            if(num_employee==0)
            {
                printf("Please input records first!\n");/**未进行数据录入提示**/
            }
            else
            {
                printf("DELETE:Please input employee ID.\n");
                ans_search=SearchbyID(num_employee,employee);
                if(ans_search==-1)
                {
                    printf("NO FOUND! FAIL TO DELETE.\n");
                }
                else
                {
                    ret=Deletedate(ans_search,num_employee,employee);
                    if(ret==0)
                    {
                        num_employee--;
                        Copyinfile(num_employee,employee);
                        printf("DELETED SUCCESSFULLY!\n");
                    }
                    else
                    {
                        printf("FAIL TO DELETE.\n");
                    }
                }
            }
        }
        if(choice==3)/**以姓名查找员工**/
        {
            if(num_employee==0)
            {
                printf("Please input records first!\n");/**未进行数据录入提示**/
            }
            else
            {
                printf("Please input employee's name:");
                ans_search=Searchbyname(num_employee,employee);
                if(ans_search==-1)
                {
                    printf("NO FOUND!\n");/**姓名不存在提示**/
                }
                else
                {
                    printf("%-10s,%d,%d/%02d/%02d,%.2f\n",employee[ans_search].name,employee[ans_search].ID,employee[ans_search].hiredate.year,employee[ans_search].hiredate.month,employee[ans_search].hiredate.day,employee[ans_search].salary);
                }
            }
        }
        if(choice==4)/**以员工号查找员工**/
        {
            if(num_employee==0)
            {
                printf("Please input records first!\n");/**未进行数据录入提示**/
            }
            else
            {
                printf("Please input employee ID:");
                ans_search=SearchbyID(num_employee,employee);
                if(ans_search==-1)
                {
                    printf("NO FOUND!\n");/**员工号不存在提示**/
                }
                else
                {
                    printf("%-10s,%d,%d/%02d/%02d,%f\n",employee[ans_search].name,employee[ans_search].ID,employee[ans_search].hiredate.year,employee[ans_search].hiredate.month,employee[ans_search].hiredate.day,employee[ans_search].salary);
                }
            }
        }
        if(choice==5)/**以入职日期查找员工**/
        {
            if(num_employee==0)
            {
                printf("Please input records first!\n");/**未进行数据录入提示**/
            }
            else
            {
                printf("Please input employee hire date:");
                ans_search=Searchbyhiredate(num_employee,employee);
                if(ans_search==-1)
                {
                    printf("NO FOUND!\n");/**员工号不存在提示**/
                }
                else
                {
                    printf("%-10s,%d,%d/%02d/%02d,%f\n",employee[ans_search].name,employee[ans_search].ID,employee[ans_search].hiredate.year,employee[ans_search].hiredate.month,employee[ans_search].hiredate.day,employee[ans_search].salary);
                }
            }
        }
        if(choice==6)/**修改指定员工号员工的薪资数据**/
        {

            if(num_employee==0)
            {
                printf("Please input records first!\n");/**未进行数据录入提示**/
            }
            else
            {
                Modify(num_employee,employee);
                Copyinfile(num_employee,employee);
            }
        }
        if(choice==7)/**统计员工数据（总数，每月薪资总和，平均工资)**/
        {
            if(num_employee==0)
            {
                printf("Please input records first!\n");/**未进行数据录入提示**/
            }
            else
            {
                printf("number of employee:%d;  SUM:%.2f;  AVEERAGE:%.2f\n",num_employee,Sum(num_employee,employee),Sum(num_employee,employee)/num_employee);
                Inputstatis(sta);
                printf("Statics is stored in file.\n");
            }
        }
        if(choice==8)/**以员工号排序**/
        {
            if(num_employee==0)
            {
                printf("Please input records first!\n");/**未进行数据录入提示**/
            }
            else
            {
                printf("Sort record in descending by ID.\n");
                OrderbyID(num_employee,employee);
                for(i=0; i<=num_employee-1; i++)
                {
                    printf("%-10s,%d,%d/%02d/%02d,%.2f\n",employee[i].name,employee[i].ID,employee[i].hiredate.year,employee[i].hiredate.month,employee[i].hiredate.day,employee[i].salary);
                }
            }
        }
        if(choice==9)/**以姓名排序**/
        {
            if(num_employee==0)
            {
                printf("Please input records first!\n");/**未进行数据录入提示**/
            }
            else
            {
                printf("Sort record in descending by name.\n");
                Orderbyname(num_employee,employee);
                for(i=0; i<=num_employee-1; i++)
                {
                    printf("%-10s,%d,%d/%02d/%02d,%.2f\n",employee[i].name,employee[i].ID,employee[i].hiredate.year,employee[i].hiredate.month,employee[i].hiredate.day,employee[i].salary);
                }
            }
        }
        if(choice==10)/**以入职时间排序**/
        {
            if(num_employee==0)
            {
                printf("Please input records first!\n");/**未进行数据录入提示**/
            }
            else
            {
                printf("Sort record in descending by hire date.\n");
                Orderbyhiredate(num_employee,employee);
                for(i=0; i<=num_employee-1; i++)
                {
                    printf("%-10s,%d,%d/%02d/%02d,%.2f\n",employee[i].name,employee[i].ID,employee[i].hiredate.year,employee[i].hiredate.month,employee[i].hiredate.day,employee[i].salary);
                }
            }
        }
        if(choice==11)/**输出所有员工记录**/
        {
            if(num_employee==0)
            {
                printf("Please input records first!\n");/**未进行数据录入提示**/
            }
            else
            {
                for(i=0; i<=num_employee-1; i++)
                {
                    printf("%-10s,%d,%d/%02d/%02d,%.2f\n",employee[i].name,employee[i].ID,employee[i].hiredate.year,employee[i].hiredate.month,employee[i].hiredate.day,employee[i].salary);
                }
            }
        }
        if(choice==0)/**退出系统**/
        {
            break;
        }
    }
    return 0;
}
