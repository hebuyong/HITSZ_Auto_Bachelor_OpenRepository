#include<iostream>
#include<math.h>
#define length 100

using namespace std;
void spl(char command[], double num[], int brackets[]);
void cal(char command[], double num[], int brackets[]);
void reset(char command[], double num[], int brackets[]);
int former(int i, char command[], double num[]);
int later(int i, int j, char command[], double num[]);
void input(char command[]);
int main()
{

	char command[length];
	double num[length] = { 0 };
	int brackets[length] = { 0 }; //1-{,2-[,3-(,4-},5-],6-)
	reset(command, num, brackets);
	//    for(int i=0; i<length&&command[i]!='='; i++)
	//    {
	//        printf("%d %c\n",i,command[i]);
	//    }

	for (int i = 1;; i++)
	{
		cout << "ÇëÊäÈë¼òµ¥ËÄÔòÔËËãËãÊ½:" << endl;
		//ÊäÈë
		input(command);
		//        for(int j=0;j<length;j++)
		//        {
		//
		//            cout<<j<<"\t"<<command[j]<<endl;
		//        }


		spl(command, num, brackets);
		//        for(int j=0; j<length&&command[j]!='='; j++)
		//        {
		//            cout<<command[j];
		//        }
		//        for(int j=0; j<length&&command[j]!='='; j++)
		//        {
		//
		//            cout<<j<<"\t"<<command[j]<<"\t"<<brackets[j]<<"\t"<<num[j]<<endl;
		//        }
		cal(command, num, brackets);
		reset(command, num, brackets);
	}

	return 0;
}
void input(char command[])
{
	char a;
	int b = 61;
	int i = 0;

	for (;;)
	{
		a = getchar();
		b = a;
		if (b == 123 || b == 125 || b == 91 || b == 93\
			|| b == 40 || b == 41 || b == 46 || b == 43 || b == 45\
			|| b == 42 || b == 47 || (b >= 48 && b <= 57) || a == '=' || a == '\n')
		{

			if (a == '=' || a == '\n')
				break;
			command[i] = a;
			i++;
		}

	}
}
void reset(char command[], double num[], int brackets[])
{
	int i, j;
	for (int i = 0; i < length; i++)
	{
		command[i] = '=';
		num[i] = 0;
		brackets[i] = 0;
	}
}

void spl(char command[], double num[], int brackets[])
{

	for (int i = 0; command[i] != '=' && i < length; i++)
	{
		switch (command[i])
		{
		case '{':
			brackets[i] = 1;
			break;
		case '}':
			brackets[i] = 2;
			break;
		case '[':
			brackets[i] = 3;
			break;
		case ']':
			brackets[i] = 4;
			break;
		case '(':
			brackets[i] = 5;
			break;
		case ')':
			brackets[i] = 6;
			break;
		case '+':
			brackets[i] = 7;
			break;
		case '-':
			brackets[i] = 8;
			break;
		case '*':
			brackets[i] = 9;
			break;
		case '/':
			brackets[i] = 10;
			break;
		case '.':
			brackets[i] = 11;
			break;
		}
	}

	for (int i = 0; command[i] != '=' && i < length; i++)
	{
		int j, k;
		if (int(command[i]) >= 48 && int(command[i]) <= 57)
		{
			num[i] = command[i] - '0';
			j = former(i, command, num);
			k = later(i, j, command, num);
			if (k != 0)
				i = k;
			else
			{
				i = j;
				cout << "wrong\n";
				/*´íÎóÊä³ö*/
			}

		}
	}

}

//Ð¡ÊýµãÇ°Êý×Ö´¦Àí
int former(int i, char command[], double num[])
{
	int j;
	for (j = i + 1; command[j] != '=' && j < length; j++)
	{
		if (int(command[j]) >= 48 && int(command[j]) <= 57)
		{
			num[i] = num[i] * 10 + command[j] - '0';
		}
		else
			break;

	}
	return j;
}

//Ð¡ÊýµãºóµÄÊý×Ö´¦Àí
int later(int i, int j, char command[], double num[])
{
	int k = 0;
	if (int(command[j]) == 46)
	{
		if (!(command[j + 1] >= 48 && command[j + 1] <= 57))
			return 0;
		else
		{
			for (int k = j + 1; command[k] != '=' && k < length; k++)
			{
				if (int(command[k]) >= 48 && int(command[k]) <= 57)
				{
					//cout<<num[i]<<"\t"<<command[k]-'0'<<"\t"<<double(pow(10,k-j))<<endl;
					num[i] = num[i] + (command[k] - '0') / double(pow(10, k - j));
				}
				else
					return k;
			}
		}
	}
	else
		return j;
	return j;
}


void cal(char command[], double num[], int brackets[])
{
	double operater1, operater2;
	int wrong = 0;
	//left´ÓµÚ¶þ¸ö´æ´¢Î»ÖÃ¿ªÊ¼´æ
	int left[50] = { 0 };
	int position = 0;
	//ÅÐ¶ÏÀ¨ºÅÊÇ·ñÆ¥Åä
	for (int i = 0; command[i] != '=' && i < length; i++)
	{
		if (brackets[i] == 1 || brackets[i] == 3 || brackets[i] == 5)
		{
			left[position + 1] = brackets[i];
			position++;
		}
		if (brackets[i] == 2 || brackets[i] == 4 || brackets[i] == 6)
		{
			if (brackets[i] == 2)
			{
				if (left[position] != 1)
				{
					wrong = i;
					break;
				}
				else
				{
					left[position] = 0;
					position--;
				}
			}
			if (brackets[i] == 4)
			{
				if (left[position] != 3)
				{
					wrong = i;
					break;
				}
				else
				{
					left[position] = 0;
					position--;
				}
			}
			if (brackets[i] == 6)
			{
				if (left[position] != 5)
				{
					wrong = i;
					break;
				}
				else
				{
					left[position] = 0;
					position--;
				}
			}
		}
	}

	//¼ì²â
	//for(int i=0;i<50;i++)
	//cout<<i<<"\t"<<left[i]<<"\t"<<wrong<<endl;

//{[10*5]*2.456+5.789*(1.45*100))
//{[10*5]*{[10*5]*2.456)+5.789*(1.45*100))
//{[10*5]*[{[10*5]*2.456+5.789*(1.45*100))
	//cout<<position<<endl;
	if (wrong != 0)
	{
		for (int i = 0; command[i] != '=' && i < length && i <= wrong; i++)
		{
			if (num[i] != 0)
			{
				cout << "²Ù×÷Êý:\t" << num[i] << endl;
			}
			if (brackets[i] != 0)
			{
				switch (brackets[i])
				{
				case 1:
					cout << "²Ù×÷·û:\t×ó´óÀ¨ºÅ\t";
					break;
				case 2:
					cout << "²Ù×÷·û:\tÓÒ´óÀ¨ºÅ\t";
					break;
				case 3:
					cout << "²Ù×÷·û:\t×óÖÐÀ¨ºÅ\t";
					break;
				case 4:
					cout << "²Ù×÷·û:\tÓÒÖÐÀ¨ºÅ\t";
					break;
				case 5:
					cout << "²Ù×÷·û:\t×óÐ¡À¨ºÅ\t";
					break;
				case 6:
					cout << "²Ù×÷·û:\tÓÒÐ¡À¨ºÅ\t";
					break;
				case 7:
					cout << "²Ù×÷·û:\t¼ÓºÅ\t";
					break;
				case 8:
					cout << "²Ù×÷·û:\t¼õºÅ\t";
					break;
				case 9:
					cout << "²Ù×÷·û:\t³ËºÅ\t";
					break;
				case 10:
					cout << "²Ù×÷·û:\t³ýºÅ\t";
					break;
				}
				if (i == wrong)
					cout << "Æ¥Åä´íÎó" << endl;
				cout << endl;
			}
		}
	}
	else
	{
		if (position == 0)
		{
			//ÕýÈ·£¬Êä³ö¼ÆËã½á¹û
			double result = 0;

			for (int j = 0; j < length && command[j] != '='; j++)
			{
				cout << command[j];
			}
			cout << "=" << result << endl;
		}
		else
		{
			for (int i = 0; command[i] != '=' && i < length; i++)
			{
				if (num[i] != 0)
				{
					cout << "²Ù×÷Êý:\t" << num[i] << endl;
				}
				if (brackets[i] != 0)
				{
					switch (brackets[i])
					{
					case 1:
						cout << "²Ù×÷·û:\t×ó´óÀ¨ºÅ\t";
						break;
					case 2:
						cout << "²Ù×÷·û:\tÓÒ´óÀ¨ºÅ\t";
						break;
					case 3:
						cout << "²Ù×÷·û:\t×óÖÐÀ¨ºÅ\t";
						break;
					case 4:
						cout << "²Ù×÷·û:\tÓÒÖÐÀ¨ºÅ\t";
						break;
					case 5:
						cout << "²Ù×÷·û:\t×óÐ¡À¨ºÅ\t";
						break;
					case 6:
						cout << "²Ù×÷·û:\tÓÒÐ¡À¨ºÅ\t";
						break;
					case 7:
						cout << "²Ù×÷·û:\t¼ÓºÅ\t";
						break;
					case 8:
						cout << "²Ù×÷·û:\t¼õºÅ\t";
						break;
					case 9:
						cout << "²Ù×÷·û:\t³ËºÅ\t";
						break;
					case 10:
						cout << "²Ù×÷·û:\t³ýºÅ\t";
						break;
					}
					if (command[i + 1] == '=')
						cout << endl << "ÎÞ·¨Æ¥Åä" << endl;
					cout << endl;
				}
			}
		}
	}
}
