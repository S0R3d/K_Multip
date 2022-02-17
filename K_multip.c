#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "K_Multip.h"

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

void K_multip(int *sum, int *s1, size_t dim1, int *s2, size_t dim2) 
{
   if (dim1 == 0 && dim2 == 0)
   {
      fprintf(stderr, "ERROR: possible loop detected!\nDimension values: %zu, %zu\n", dim1,dim2);
      exit(1);
   }
   
   if (dim1 != 2 && dim2 != 2)
   {
      K_multip(sum, s1, dim1/2, s2, dim2/2);

      K_multip(&sum[dim1/2+dim2/2], &s1[dim1/2], dim1-dim1/2, &s2[dim2/2], dim2-dim2/2);
      
      int* sumapp = (int*)malloc(sizeof(int) * dim1);
      int* sumapp1 = (int*)malloc(sizeof(int) * dim1);

      K_multip(sumapp, s1, dim1/2, &s2[dim2/2], dim2-dim2/2);
      
      K_multip(sumapp1, &s1[dim1/2], dim1-dim1/2, s2, dim2/2);
      
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