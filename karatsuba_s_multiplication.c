// cSpell: Disable
// God blessed then and said:
// "Be fruitful and MULTIPLY..." - Genesis 1:22

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Unsigned long int, size_t
#define INF 0x8000000000000000

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

void print_digits(char prev[], int *s, size_t dim) {
   printf("%s dim:%zu\n", prev, dim);
   for (size_t i = 0; i < dim; i++)
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
   if (*ptr1 & 1)
      *ptr1 += 1, *ptr2 += 1;
   while (!(!(*ptr1 & (*ptr1 - 1)) && *ptr1)) {
      *ptr1 += 1, *ptr2 += 1;
   }
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
// FIXME: change func, 'cause has to check s1 and s2 within
// type and value returned?
// TODO: check if dimensions if corrent after modify them:
// 1 dim even
// 2 dim1 = dim2
int zeros_check(int* s1, size_t* dim1, size_t* dim2) {
   // here below *dim1 =,== *dim2
   if (*dim1 == *dim2) {
      // n. of zero in array 
      size_t zeros = 0;
      // zeros' positions
      int pos[*dim1];

      print_digits("preloop-pos: ", pos, *dim1);
      for (size_t i = 0; i < *dim1; ++i) {
         if (*(s1+i) == 0) {
            pos[zeros] = i;
            zeros++;
         } else pos[zeros] = 0;
      }
      print_digits("postloop-pos: ", pos, *dim1);
      
      // all 0, result of multip = 0
      if (zeros == *dim1) return 0;

      for (size_t i = zeros, y = *dim1; i-- > 0 && y-- > 0 ; ) {
         // check if zeros are in supp. half of array
         if (pos[i] != (int)y) if (y+1 != *dim1) *dim1 = y+1;
      }
      return 1;
   } else if (*dim1 != *dim2) {
      printf("not implemented!\n");
      // forse non sono mai diversi perche check_sizes corregge la diversità
      return -1;
   } else return -1;
}

void K_core(int *sum, int *s1, size_t dim1, int *s2, size_t dim2) 
{
   if (dim1 == 0 && dim2 == 0)
   {
      fprintf(stderr, "ERROR: possible loop detected!\nDimension values: %zu, %zu\n", dim1,dim2);
      exit(1);
   }
   
      printf("pre-dim1:%zu, pre-dim2:%zu \n\n", dim1, dim2);
      int res = zeros_check(s1, &dim1, &dim2);
      if ( res == 0) {
         // moltip di soli zeri si salta la roba sotto
         // modificare sum e creare un metodo per saltare l'if che segue(tipo ritornare la funzione 'cause ricorsiva)
         printf("res 0\n");
         for (size_t i = 0; i < dim1+dim2; i++)
            *(sum+i) = 0;
         return;
      } else if (res == 1) {
         // potrei aver tolto degli zeri ma la moltip. va fatta comunque
         // dim1 e/o dim2 aggionati
         printf("res 1\n");
         
      } else {
         fprintf(stderr, "ERROR: dimensions reduces fails!\nDimension value: %zu, %zu\n", dim1,dim2);
         exit(1);
      }
      printf("post-dim1:%zu, after-dim2:%zu \n\n", dim1, dim2);
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

   print_digits("s1 - input: ", s1, dim1);
   print_digits("s2 - input: ", s2, dim2);

   
   K_core(sum, s1, dim1, s2, dim2);

   
   printf("---------------------------\n");
   for (size_t i = 0; i < (dim1+dim2); i++)
      printf("sum: %d\n", sum[i]);

   for (size_t i = 0; i < (dim1+dim2); i++)
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
