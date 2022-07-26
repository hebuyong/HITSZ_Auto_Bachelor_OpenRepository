#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Number:190410102\nsubject No.1-program No.1\n\n");
    char a;
    int b,f;
    short int c;
    float d;
    double e;
    printf("please input char a:");
    scanf("%c",&a);
    f=sizeof(a);
    printf("char a=%c,sizeof char=%d\n",a,f);
    printf("please input int b:");
    scanf("%d",&b);
    f=sizeof(b);
    printf("int b=%d,sizeof int=%d\n",b,f);
    printf("please input short int c:");
    scanf("%hd",&c);
    f=sizeof(c);
    printf("short int c=%hd,sizeof short int=%d\n",c,f);
    printf("please input float d:");
    scanf("%f",&d);
    f=sizeof(d);
    printf("float d=%f,sizeof float=%d\n",d,f);
    printf("please input double e:");
    scanf("%lf",&e);
    f=sizeof(e);
    printf("double e=%f,sizeof double=%d\n",e,f);
    printf("THE END OF PROGRAM\n");
    return 0;
}
