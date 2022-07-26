#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED
#define MAX_EMPLOYEE 30
#define MAX_NAMELINE 21

struct Employ
{
    char name[MAX_NAMELINE];
    int ID;
    float salary;
} employee[MAX_EMPLOYEE];


void PrintfChoice();
void InputDate(int num,struct Employ emp[]);
void Orderbysalary(int num,struct Employ emp[]);
void Orderbyname(int num,struct Employ emp[]);
int Searchbyname(int num,struct Employ emp[]);
int SearchbyID(int num,struct Employ emp[]);



#endif // FUNCTION_H_INCLUDED
