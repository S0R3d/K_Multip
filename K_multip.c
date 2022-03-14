#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "K_multip.h"

void R_number_to_digits(int n, int *s, size_t dim) {
   for (size_t i = 0; i < dim; i++)
   {
      *(s+i) = n%10;
      n /= 10;
   }
}

void number_to_digits(int n, int *s, size_t dim) {
   for (size_t i = dim; i-- > 0; )
   {
      *(s+i) = n%10;
      n /= 10;
   }
}

void check_sizes(size_t* ptr1, size_t* ptr2) {
   if (*ptr1 != *ptr2) {
      if (*ptr1 != *ptr2 && *ptr1 > *ptr2)
         *ptr2 += (*ptr1) - (*ptr2);
      if (*ptr1 != *ptr2 && *ptr2 > *ptr1)
         *ptr1 += (*ptr2) - (*ptr1);
   }
   if (*ptr1 & 1)
      *ptr1 += 1, *ptr2 += 1;
   while (!(!(*ptr1 & (*ptr1 - 1)) && *ptr1))
      *ptr1 += 1, *ptr2 += 1;
}

void carry_over_to_digits(int *s, size_t dim) {
   for (size_t i = 0; i < dim; i++) {
      size_t dimN = floor(log10(abs(s[i])))+1;
      if (dimN != 1) {
         int r = *(s+i)%10;
         int d = *(s+i)/10;

         if (i != dim-1) {
            *(s+i) = r;
            *(s+(i+1)) += d;
         }
      }
   }
}

void sum_digits(int *s1, int *s2, size_t dim) {
   for (size_t i = 0; i < dim; i++)
      *(s1+i) += *(s2+i);

   carry_over_to_digits(s1, dim);
}

void K_core(int *sum, int *s1, size_t dim1, int *s2, size_t dim2) 
{
   if (dim1 == 0 && dim2 == 0)
   {
      fprintf(stderr, "ERROR: possible loop detected!\nDimension values: %zu, %zu\n", dim1,dim2);
      exit(1);
   }
   
   if (dim1 != 2 && dim2 != 2)
   {
      K_core(sum, s1, dim1/2, s2, dim2/2);

      K_core(&sum[dim1/2+dim2/2], &s1[dim1/2], dim1-dim1/2, &s2[dim2/2], dim2-dim2/2);
      
      int* sumapp = (int*)malloc(sizeof(int) * dim1);
      int* sumapp1 = (int*)malloc(sizeof(int) * dim1);

      K_core(sumapp, s1, dim1/2, &s2[dim2/2], dim2-dim2/2);
      
      K_core(sumapp1, &s1[dim1/2], dim1-dim1/2, s2, dim2/2);
      
      sum_digits(sumapp, sumapp1, dim1);
      
      sum_digits(&sum[(dim1+dim2)/4], sumapp, dim1); 

      free(sumapp);
      free(sumapp1);
   } else {
      *(sum) = *s1 * *s2;
      *(sum+1) = ( *(s1) * *(s2+ dim2 -1) ) + ( *(s1+ dim1 -1) * *(s2) );
      *(sum+2) = *(s1+ dim1 -1) * *(s2+ dim2 -1);
      *(sum+3) = 0;

      carry_over_to_digits(sum, dim1+dim2);
   }
}

long long K_multip(long long a, long long b) {
   long long r = 0;

   size_t dim1 = floor(log10(llabs(a)))+1;
   size_t dim2 = floor(log10(llabs(b)))+1;

   check_sizes(&dim1, &dim2);

   int* sum = (int*)malloc(sizeof(int) * (dim1+dim2));

   int* s1 = (int*)malloc(sizeof(int) * dim1);
   R_number_to_digits(a, s1, dim1);

   int* s2 = (int*)malloc(sizeof(int) * dim2);
   R_number_to_digits(b, s2, dim2);
   
   K_core(sum, s1, dim1, s2, dim2);

   for (size_t i = 0; i < (dim1+dim2); i++)
      r += (sum[i] * (long long)pow(10,(double)i));
   
   free(s1);
   free(s2);
   free(sum);

   return r;
}
