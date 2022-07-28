#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/***************
**判断一个数是否为质数，并分解质因数

程序1：(1):判断是否为质数中，For循环中查找因数时只需要到sqrt(num)，
若不明白请重新查看实验四说明文档中的内容。
(2): 修改成除法余数为0则count+1 ，那么只需要判断count==1即可判断是否为素数。
***************/

int main()
{
    printf("Number:190410102\nsubject No.4-program No.1\n\n");

    int number,num,i,j,k,count;
    char ans;

    //循环判断
    for(k=1;; k++)
    {


        //输入一个数
        printf("请输入一个想要判断是否为质数的正整数：");
        scanf("%d",&number);
        count=0;
        num=number;//nun用于中间值

        //数为1,2时
        if(number==1)
        {
            printf("It's neither a prime nor decomposable.\n");
        }
        /**revise**/
       /*if(number==2)
       {
           printf("2=1*2\n");
        }*/

        //数大于2
        if(number>=2)
        {
            /**revise:sqrt**/
            for(i=1; i<=sqrt(number); i++)//得到非因子数
            {
                if(number%i==0)
                    count++;
                else
                {
                    ;
                }
            }

            if(count==1)//判断为质数
            {
                printf("It's a prime number.\n");
            }

            else//判断为非质数
            {
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
        }

        //询问是否继续判断
        printf("Do you want to continue?\nYes please type 'y'or 'Y', no please type 'n' or 'N'.  ");
        while(getchar()!='\n');
        scanf("%c",&ans);
        if(ans=='y'||ans=='Y');
        else
            break;
    }
    return 0;
}
