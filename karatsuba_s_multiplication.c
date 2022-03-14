// cSpell: Disable
// God blessed then and said:
// "Be fruitful and MULTIPLY..." - Genesis 1:22

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Unsigned long int, size_t means Infinity
#define INF 0x8000000000000000

void R_number_to_digits(int n, int *s, size_t dim) {
   for (size_t i = 0; i < dim; ++i)
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

void print_digits(char prev[], int *s, size_t dim) {
   printf("%s dim:%zu\n", prev, dim);
   for (size_t i = 0; i < dim; ++i)
      printf("pos %zu: %d\n", i, *(s+i));
   printf("\n");
}

void check_sizes(size_t* ptr1, size_t* ptr2) {
   if (*ptr1 & INF)
      *ptr1 = 1;
   if (*ptr2 & INF)
      *ptr2 = 1;
   if (*ptr1 != *ptr2) {
      if (*ptr1 != *ptr2 && *ptr1 > *ptr2)
         *ptr2 += (*ptr1) - (*ptr2);
      if (*ptr1 != *ptr2 && *ptr2 > *ptr1)
         *ptr1 += (*ptr2) - (*ptr1);
   }
   if (*ptr1 & 1 || *ptr2 & 1)
      *ptr1 += 1, *ptr2 += 1;
   while (!(!(*ptr1 & (*ptr1 - 1)) && *ptr1)) {
      *ptr1 += 1, *ptr2 += 1;
   }
}

void carry_over_to_digits(int *s, size_t dim) {
   for (size_t i = 0; i < dim; ++i) {
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
   for (size_t i = 0; i < dim; ++i)
      *(s1+i) += *(s2+i);

   carry_over_to_digits(s1, dim);
}

/**
 * Exit code function:
 * -1 -> nessuno zero
 * 0  -> tutti zeri
 * 1  -> alcuni zeri (rimossi ?)
 */
// FIXME: NOT WORK
int zero_decrease(int* s1, size_t* d1, int*s2, size_t* d2, size_t* res1, size_t* res2) {
   if (*d1 != *d2)
   {
      fprintf(stderr, "ERROR: Dimensions are not equals! Please use 'check_size()' before call this function");
      exit(1);
   }
   
   size_t z1 = 0, z2 = 0;
   int p1[*d1], p2[*d2];

   for (size_t i = 0; i < *d1; ++i) {
      if (*(s1+i) == 0) {
         p1[z1] = i;
         ++z1;
      } else p1[z1] = 0;
   }
   for (size_t i = z1; i < *d1; ++i)
      p1[i] = 0;
   for (size_t i = 0; i < *d2; ++i) {
      if (*(s2+i) == 0) {
         p2[z2] = i;
         ++z2;
      } else p2[z2] = 0;
   }
   for (size_t i = z2; i< *d2; ++i)
      p2[i] = 0;
   
   if (z1 == *d1 && z2 == *d2) return 0;
   if (z1 == 0 && z2 == 0) return -1;
   
   if ( z1 >= *d1/2+1 ) {
      for (size_t i = z1, y = *d1; i-- > 0 && y-- > 0 ;) {
         if (p1[i] != (int)y) if (y+1 != *d1) {
            *d1 = y+1;
            break;
         }
      }
   }
   if ( z2 >= *d2/2+1) {
      for (size_t i = z2, y = *d2; i-- > 0 && y-- > 0 ;) {
         if (p2[i] != (int)y) if (y+1 != *d2) {
            *d2 = y+1;
            break;
         }
      }
   }
   if (*d1%2 != 0 && *d2%2 != 0) {
      *d1 += 1, z1 += 1;
      *d2 += 1, z2 += 1;
   }
   *res1 = z1, *res2 = z2;
   return 1;
}

void zero_increase(int* sum, size_t* dim1, size_t* dim2, size_t res1, size_t res2) {
   size_t this_dim1 = *dim1, this_dim2 = *dim2;
   *dim1 += res1;
   *dim2 += res2;

   for (size_t i = this_dim1+this_dim2; i < *dim1+*dim2; ++i)
      *(sum+i) = 0;
}

void K_core(int *sum, int *s1, size_t dim1, int *s2, size_t dim2) 
{
   if (dim1 == 0 && dim2 == 0)
   {
      fprintf(stderr, "ERROR: possible loop detected!\nDimension values: %zu, %zu\n", dim1, dim2);
      exit(1);
   }
   
   size_t res1, res2;
   int op = zero_decrease(s1, &dim1, s2, &dim2, &res1, &res2);
   if ( op == 0) {
      printf("op-code: %d\n", op);
      printf("Rilevati SOLO zeri, operazioni non eseguite\n");
      for (size_t i = 0; i < dim1+dim2; ++i)
         *(sum+i) = 0;
      return;
   } else if (op == -1) {
      printf("op-code: %d\n", op);
      printf("Nessuno zero rilevato, operazioni non eseguite\n");
   } else if (op == 1) {
      printf("op-code: %d\n", op);
      printf("Zeri rilevati, operazioni eseguite\n");
      printf("dim: %zu,%zu\n", dim1, dim2);
   } else {
      printf("op-code: %d\n", op);
      fprintf(stderr, "ERROR: dimensions reduces fails!\nDimension value: %zu, %zu\n", dim1,dim2);
      exit(1);
   }

   if (dim1 != 2 && dim2 != 2) {

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

      // zero_increase(sum, &dim1, &dim2, res1, res2);
   }
}

void user_input(long long* n1, long long* n2) {
   printf("Int - Numbers Range: 0, 1 - 9, 10 - 99, 100 - 999, 1000 - 4999\n");
   printf("Long Long - Numbers Range: 0, 1 - 9, 10 - 99, 100 - 999, 1000 - 9999, 10000 - 99999, perhaps beyond these \n\n");
   printf("Insert first number: ");
   scanf("%lld", n1);
   printf("Insert second number: ");
   scanf("%lld", n2);
   printf("\n");
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

   print_digits("first digit input:   ", s1, dim1);
   print_digits("second digit input: ", s2, dim2);
   
   K_core(sum, s1, dim1, s2, dim2);

   printf("---------------------------\n");
   for (size_t i = 0; i < (dim1+dim2); ++i)
      printf("sum: %d\n", sum[i]);

   for (size_t i = 0; i < (dim1+dim2); ++i)
      r += (sum[i] * (long long)pow(10,(double)i));
   
   free(s1);
   free(s2);
   free(sum);
   return r;
}

int main() {
   long long n1,n2;
   long long p = 0;

   user_input(&n1, &n2);

   p = K_multip(n1,n2);
   
   printf("---------------------------\n");
   printf("Multip. Karatsuba's Method: %lld\n", p);
   printf("Multip. STD Method:         %lld\n", n1*n2);
   printf("Difference:                 %lld\n", (n1*n2) - p);
   printf("---------------------------\n");

   return 0;
}
