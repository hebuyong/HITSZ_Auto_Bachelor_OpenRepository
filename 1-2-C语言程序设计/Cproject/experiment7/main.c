#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

/**************************
**员工姓名、员工号、工资
数据输入，排序，查找系统V3.0
**************************/
#define MAX_EMPLOYEE 30

int main()
{
    printf("Number:190410102\nsubject No.7-program No.1\n\n");

    /**choice用于用户选择ret用于判断数据输入正误,
    ans_search用于接收搜索结果，count用于记录是否输入数据,
    employ用于记录姓名、员工号、薪资**/
    int choice,ret,i,ans_search,num_employee,count=0;


    /**输入员工数并进行正确性检查**/
    printf("Please input employee number(1<=n<=30):");
    ret=scanf("%d",&num_employee);
    while(ret!=1||num_employee<1||num_employee>MAX_EMPLOYEE)
    {
        printf("Please input employee number(1<=n<=30):");
        while(getchar()!='\n');
        ret=scanf("%d",&num_employee);
    }

    /**系统循环使用**/
    for(;;)
    {

        PrintfChoice();

        /**输入用户选择并进行准确性检查**/
        ret=scanf("%d",&choice);
        while(ret!=1||choice<0||choice>5)
        {
            printf("Please input choice(0,1,2,3,4,5):");
            while(getchar()!='\n');
            ret=scanf("%d",&choice);
        }

        if(choice==1)/**输入数据并按薪资降序排序**/
        {
            InputDate(num_employee,employee);
            count=1;
            Order(num_employee,employee);
        }

        if(choice==2)/**输出排序结果**/
        {
            if(count==0)
            {
                printf("Please input records first!\n");/**未进行数据录入提示**/
            }
            else
            {
                for(i=0; i<=num_employee-1; i++)
                {
                    printf("NO.%d name:%c ID:%d  salary:%d\n",i+1,employee[i].name,employee[i].ID,employee[i].salary);
                }
            }
        }

        if(choice==3)/**以姓名查找员工**/
        {
            if(count==0)
            {
                printf("Please input records first!\n");/**未进行数据录入提示**/
            }
            else
            {
                ans_search=Searchbyname(num_employee,employee);
                if(ans_search==-1)
                {
                    printf("NO FOUND!\n");/**姓名不存在提示**/
                }
                else
                {
                    printf("name:%c  ID:%d  salary:%d\n",employee[ans_search].name,employee[ans_search].ID,employee[ans_search].salary);
                }
            }
        }

        if(choice==4)/**以员工号查找员工**/
        {
            if(count==0)
            {
                printf("Please input records first!\n");/**未进行数据录入提示**/
            }
            else
            {
                ans_search=SearchbyID(num_employee,employee);
                if(ans_search==-1)
                {
                    printf("NO FOUND!\n");/**员工号不存在提示**/
                }
                else
                {
                    printf("name:%c  ID:%d  salary:%d\n",employee[ans_search].name,employee[ans_search].ID,employee[ans_search].salary);
                }
            }

        }

        if(choice==5)/**输出记录**/
        {
            if(count==0)
            {
                printf("Please input records first!\n");/**未进行数据录入提示**/
            }
            else
            {
                for(i=0; i<=num_employee-1; i++)
                {
                    printf("name:%c  ID:%d  salary:%d\n",employee[i].name,employee[i].ID,employee[i].salary);
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
