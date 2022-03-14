#include <stdio.h>
#include <stdlib.h>

#include "K_multip.h"

typedef long long ll;

int main () {
   ll a, b;

   printf("Inserts two numbers: \n");
   scanf("%lld",&a);
   scanf("%lld",&b);

   ll res = K_multip(a,b);

   printf("Result: %lld\n", a*b);
   printf("Result: %lld\n", res);
   return 0;
}
