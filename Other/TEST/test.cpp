#include<stdio.h>
typedef int (*FP_CALC)(int, int);
int add(int a, int b);
int sub(int a, int b);
FP_CALC calc_func(char op);
int calc(int a, int b, char op);
int _NULL(int a, int b);

int _NULL(int a, int b) {
	return 0;
}

int add(int a, int b)
{
     return a + b;
}
int sub(int a, int b)
{
     return a - b;
}
FP_CALC calc_func(char op) {
     switch (op)
     {
     case '+': return add;//返回函数的地址
     case '-': return sub;
     default:
         return _NULL;
     }
}
int calc(int a, int b, char op) {
     FP_CALC fp = calc_func(op);
     if (fp) return fp(a, b);
     else return -1;
}
int main()
{   
  int a = 100, b = 20;
  printf("calc(%d, %d, %c) = %d\n", a, b, '+', calc(a, b, '+'));
  printf("calc(%d, %d, %c) = %d\n", a, b, '-', calc(a, b, '-'));
	return 0;
}
