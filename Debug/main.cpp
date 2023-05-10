#include <stdio.h>
#include "maths.h"

int main(int argc, char const *argv[])
{
    
    printf("Sum is %d \n",addition(8,7));
    printf("Difference is %d \n",soustraction(8,7));
    printf("Product is %d \n",multiplication(8,7));
    int etat = 0;
    float res = division(8,0,&etat);
    printf("Quotient is %d %f \n",etat,res);
}
