#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Number:190410102\nsubject No.3-program No.1\n\n");
    int total,n5,n2,n1,i,ret;
    printf("请输入将要兑换的人民币金额(不超过100元）:");
    ret=scanf("%d",&total);
    while(ret!=1||total<=0||total>100)
    {
        while(getchar()!='\n');
        printf("请输入将要兑换的人民币金额(不超过100元）:");
        ret=scanf("%d",&total);
    }
    n5=total/5;
    n2=(total%5)/2;
    n1=total%5-2*n2;
    printf("最优组合：五元%02d张，两元%02d张，一元%02d张,共%02d张\n\n",n5,n2,n1,n5+n2+n1);
    i=1;
    while(n5>=0)
    {
        n1=total-5*n5;
        n2=0;
        printf("第%03d种为：五元%02d张，两元%02d张，一元%02d张,共%02d张\n",i,n5,n2,n1,n5+n2+n1);
        while(n1>=2)
        {
            i++;
            n1-=2;
            n2+=1;
            printf("第%03d种为：五元%02d张，两元%02d张，一元%02d张,共%02d张\n",i,n5,n2,n1,n5+n2+n1);
        }
        n5--;
        i++;
    }
    printf("共%03d种",i-1);
    return 0;
}
