#include "stdafx.h"
#include "string.h"

char s1[1000], s2[1000];
int n1[1000], n2[1000];//全局变量默认为所有元素初始值为0
int sum[1010];//同上
int main()
{
	  //使用scanf_s 时需要给定后面一个参数，即最大的字符输入个数，防止溢出，覆盖其他内存的变量，造成系统错误。
	    scanf_s("%s", s1,1000);
	    scanf_s("%s", s2,1000);

	    printf("s1=%s,len=%d\n", s1, strlen(s1));
		printf("s2=%s,len=%d\n", s2, strlen(s2));
		memset(n1, 0, sizeof(n1));//数字归0
		memset(n2, 0, sizeof(n2));
		for (int i = 0; i < strlen(s1); i++)//字符串123 ，倒序存入数组中为321，目的是为了方便计算
		{
			n1[i] = s1[strlen(s1) - 1 - i] - '0';
		}
		for (int i = 0; i < strlen(s2); i++)//第二个倒序存入n2
		{
			n2[i] = s2[strlen(s2) - 1 - i] - '0';
		}
		for (int i = 0; i <  (strlen(s1) >= strlen(s2) ? strlen(s1) : strlen(s2)) ; i++) //循环次数为 大的数的位数
		{
			sum[i] = n1[i] + n2[i]; //一位一位加  在倒序排列的情况下，数组中存放的数的位数为：个十百千万，与实际中的写法相反
			if (sum[i] >= 10)      //然后就是进位
			{
				sum[i + 1]++;
				sum[i] -= 10;
			}
		}
		//(strlen(s1) >= strlen(s2) ? strlen(s1) : strlen(s2))
		//加法运算，两个数中的最大数的位数为n时，那么加法的结果，最大位数为n+1； 当 max ( strlen(s1),strlen(s2) ) =2时，则 i取值= 2 1 0 
		//实际上遍历了最大位数的位置n+1 ;
		for (int i = (strlen(s1) >= strlen(s2) ? strlen(s1) : strlen(s2)); i >= 0; i--)
		{
			if (sum[i] != 0)                //直到某位不为0   从后往前找不为0的数，也就是找到不为0的最高位。
			{
				for (int j = i; j >= 0; j--)//打印结果
				{
					printf("%d", sum[j]);
				}
				break;
			}
		}
		printf("\n");
	
	return 0;
}
