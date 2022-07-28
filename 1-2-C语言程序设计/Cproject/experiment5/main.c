#include <stdio.h>
#include <stdlib.h>
#include "function.h"

/**************************
**输入，排序，查找系统
**************************/

int main()
{
    printf("Number:190410102\nsubject No.5-program No.1\n\n");

    /**choice用于用户选择ret用于判断数据输入正误,
    ans_search用于接收搜索结果，count用于记录是否输入数据,
    List为员工号，Salary为员工工资，ave用于接收平均值**/
    int choice,ret,i,ans_search,num_employee,count=0;
    int list[30];
    double salary[30];
    double ave;

    /**输入员工数并进行正确性检查**/
    printf("Please input employee number(1<=n<=30):");
    ret=scanf("%d",&num_employee);
    while(ret!=1||num_employee<1||num_employee>30)
    {
        printf("Please input employee number(1<=n<=30):");
        while(getchar()!='\n');
        ret=scanf("%d",&num_employee);
    }

    /**系统循环使用**/
    for(;;)
    {
        PrintfChoice();
        scanf("%d",&choice);

        if(choice==1)/**输入数据并排序**/
        {
            InputDate(num_employee,list,salary);
            count=1;
            Order(num_employee,list,salary);
        }

        if(choice==2)/**计算工资平均值**/
        {
            if(count==0)
            {
                printf("Please input records first!\n");/**未进行数据录入提示**/
            }
            else
            {
                ave=Average(num_employee,salary);
                printf("%lf\n",ave);
            }
        }

        if(choice==3)/**输出排序结果**/
        {
            if(count==0)
            {
                printf("Please input records first!\n");/**未进行数据录入提示**/
            }
            else
            {
                for(i=0; i<=num_employee-1; i++)
                {
                    printf("NO.%d  %d  %lf\n",i+1,list[i],salary[i]);
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
                ans_search=Search(num_employee,list);
                if(ans_search==-1)
                {
                    printf("NO FOUND!\n");/**员工号不存在提示**/
                }
                else
                {
                    printf("%d  %lf\n",list[ans_search],salary[ans_search]);
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
                    printf("%d  %lf\n",list[i],salary[i]);
                }

            }

        }

        if(choice==6)/**退出系统**/
        {
            break;
        }

    }

    return 0;
}
