#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED
#define MAX_EMPLOYEE 30
#define MAX_NAMELINE 21
typedef struct date
{
    int year;
    int month;
    int day;
} DATE;
typedef struct Employ
{
    char name[MAX_NAMELINE];
    int ID;
    DATE hiredate;
    float salary;
} EMPLOY;

typedef struct statis
{
    int num_employee;
    float sum;
    float ave;
} STATIS;
void  Addinfile(int num,EMPLOY emp[]);
void  Copyoutfile(int num,EMPLOY emp[]);
void  Copyinfile(int num,EMPLOY emp[]);
int   Deletedate(int n,int num,EMPLOY emp[]);
void  PrintfChoice();
int   Getemployee_num();
void  Inputdate(int num,EMPLOY emp[]);
void  OrderbyID(int num,struct Employ emp[]);
void  Orderbyname(int num,struct Employ emp[]);
void  Orderbyhiredate(int num,EMPLOY emp[]);
int  Searchbyname(int num,struct Employ emp[]);
int  SearchbyID(int num,struct Employ emp[]);
int  Searchbyhiredate(int num,EMPLOY emp[]);
void Modify(int num,EMPLOY emp[]);
float Sum(int num,EMPLOY emp[]);
void Inputstatis(STATIS sta);
#endif // FUNCTION_H_INCLUDED
