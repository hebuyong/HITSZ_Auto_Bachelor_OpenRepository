#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED
#define MAX_EMPLOYEE 30

struct Employ
{
    char name;
    int ID;
    int salary;
} employee[MAX_EMPLOYEE];


void PrintfChoice();
void InputDate(int num,struct Employ emp[]);
void Order(int num,struct Employ emp[]);
int Searchbyname(int num,struct Employ emp[]);
int SearchbyID(int num,struct Employ emp[]);



#endif // FUNCTION_H_INCLUDED
