# include "maths.h"
int addition(int a, int b)
{
    return a+b;
}

int soustraction(int a , int b)
{
    return a-b;
}

int multiplication(int a, int b)
{
    return a*b;
}

float division(float a , float b,int* etat)
{
	if(b == 0)
	{
		*etat = 0;
		return 0.0;
    }
    *etat = 1;
    return a/b;
}
