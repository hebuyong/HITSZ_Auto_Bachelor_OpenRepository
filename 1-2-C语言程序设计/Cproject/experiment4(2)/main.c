#include <stdio.h>
#include <stdlib.h>

/*********************
**判断数是否为完全数
*********************/

int main()
{
    printf("Number:190410102\nsubject No.4-program No.2\n\n");



    int number,num,i,j;
    char ans;

    //循环判断
    for(j=1;;j++)
    {


        //输入一个数
        printf("请输入一个想要判断是否为完全数的正整数：");
        scanf("%d",&number);
        num=0;

        if(number==1)
        {
            printf("It's not a perfect number.\n");
        }

        if(number>=2)
        {
            for(i=1; i<=number-1; i++)//计算不同因子的和
            {
                if(number%i==0)
                {
                    num+=i;
                }

            }

            if(num==number)//判断为完全数
            {
                printf("It's a perfect number.\n");
                printf("%d=1",number);
                for(i=2; i<=number-1; i++)
                {
                    if(number%i==0)
                    {
                        printf("+%d",i);
                    }

                }
                printf("\n");

            }

            else//判断为非完全数
            {
                printf("It's not a perfect number.\n");
            }
        }

        //是否继续判断
        printf("Do you want to continue?\nYes please type 'y'or 'Y', no please type 'n' or 'N'.   ");
        while(getchar()!='\n');
        scanf("%c",&ans);
        if(ans=='y'||ans=='Y')
            ;
        else
            break;


    }
    return 0;
}
