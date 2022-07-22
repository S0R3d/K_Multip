#include <iostream>
#include <cmath>

#include "K_multip.h"

typedef long long ll;

void R_number_to_digits(int n, int *s, size_t dim) {

}

void number_to_digits(int n, int *s, size_t dim) {

}

void check_sizes(size_t* dim1, size_t* dim2) {

}

void carry_over_to_digits(int *s, size_t dim) {

}

void sum_digits(int *s1, int *s2, size_t dim) {

}

void K_core(int *sum, int *s1, size_t dim1, int *s2, size_t dim2) {

}

ll K_multip(int first, int second) {
   
}

ll K_multip(ll first, ll second) {
   ll res = 0;
   size_t d1 = floor(log10(llabs(first)))+1;
   size_t d2 = floor(log10(llabs(second)))+1;
   check_sizes(&d1, &d2);

   int* sum = (int*)malloc(sizeof(int) * (d1+d2));
   int* s1 = (int*)malloc(sizeof(int) * d1);
   R_number_to_digits(first, s1, d1);
   int* s2 = (int*)malloc(sizeof(int) * d2);
   R_number_to_digits(second, s2, d2);

   K_core(sum,s1,d1,s2,d2);

   for(size_t i = 0; i< d1+d2; ++i)
      res += (sum[i]*(ll)pow(10,(double)i));
   
   free(s1);
   free(s2);
   free(sum);
   return res;
}
