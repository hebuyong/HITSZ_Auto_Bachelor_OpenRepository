#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main()
{
    printf("Number:190410102\nsubject No.2-program No.1\n\n");

    int a,b,c,i,ans;
    double ans1;
    char que;
    for(i=1;i<=10;i++)
    {
        srand(time(NULL));
        a=rand()%10+1;
        b=rand()%10+1;
        c=rand()%4 +1;
        switch(c)
        {
        case 1:
            {
                que='+';
                ans=a+b;
                break;
            }
        case 2:
            {
                que='-';
                ans=a-b;
                break;
            }
        case 3:
            {
                que='*';
                ans=a*b;
                break;
            }
        case 4:
            {
                que='/';
                ans=a/b;
                break;
            }
            default:
            printf("switch is wrong.");
        }
        printf("%d%c%d=",a,que,b);
        scanf("%lf",&ans1);
        if(ans1==ans)
        {
            printf("Very good!");
        }
        else
            {
                if(fabs(ans-ans1)<=0.1*fabs(ans)+1e-5)
                {
                    printf("Very close to the answer!");
                }
                else
                {
                    if(fabs(ans1-ans)<0.2*fabs(ans)-1e-5)
                    {
                        printf("Wrong answer, Keep trying!");
                    }
                    else
                    {
                        printf("Please learn ¡°Four Arithmetic Operations¡± again!");
                    }
                }
            }
        printf("\n");

    }
    printf("\nThe end of program.");

    return 0;
}
