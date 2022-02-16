// cSpell: Disable
// God blessed then and said:
// "Be fruitful and MULTIPLY..." - Genesis 1:22

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function that converts a number in digits and store in split (less sign. digit -> less sign. posizion)
void R_number_to_digits(int n, int *s, size_t dim) {
   for (size_t i = 0; i < dim; i++)
   {
      *(s+i) = n%10;
      n /= 10;
   }
}

// Function that converts a number in digits and store in a split (more sign. digit -> less sign. posizion)
void number_to_digits(int n, int *s, size_t dim) {
   for (size_t i = dim; i-- > 0; )
   {
      *(s+i) = n%10;
      n /= 10;
   }
}

// Function that prints digits in a split
void print_digits(char prev[], int *s, size_t dim) {
   printf("%s dim:%zu\n", prev, dim);
   for (size_t i = 0; i < dim; i++)
      printf("pos %zu: %d\n", i, *(s+i));
   printf("\n");
}

// Function that controll if 'dimension' is even and if isn't add +1
void check_sizes(size_t* ptr1, size_t* ptr2) {
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

// Function that reduces number in a split (2+ digits) in digits on the same split
// - It takes into account the carry-overs given by the sum
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

// Function that sums digits value from 2 splits and store in the first one
void sum_digits(int *s1, int *s2, size_t dim) {
   for (size_t i = 0; i < dim; i++)
      *(s1+i) += *(s2+i);

   carry_over_to_digits(s1, dim);
}

// K-Multiplication of 2/1 digits in splits
void K_multip_2dig(int *sum, int *s1, size_t dim1, int *s2, size_t dim2)
{
   *(sum) = *s1 * *s2;
   *(sum+1) = ( *(s1) * *(s2+ dim2 -1) ) + ( *(s1+ dim1 -1) * *(s2) );
   *(sum+2) = *(s1+ dim1 -1) * *(s2+ dim2 -1);
   *(sum+3) = 0;

   carry_over_to_digits(sum, dim1+dim2);
}

// K-Multiplication of 4/3, 2/1 digits in splits
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
   } else K_multip_2dig(sum, s1, dim1, s2, dim2);
}

// Function that receves input numbers from user
void user_input(long long* n1, long long* n2) {
   printf("Numbers Range: 0, 1 - 9, 10 - 99, 100 - 999, 1000 - 9999 \n");
   printf("Insert first number: ");
   scanf("%lld", n1);
   printf("Insert second number: ");
   scanf("%lld", n2);
}

// TODO: funzione da chiamare dall'esterno che fa funzionare K_Multip senza il main
// Trasforma i numeri in array di digits e regola le dimensioni, alla fine raggruppa i digits nel risultato
void between_main_multip() {}

int main() {
   long long n1,n2;

   user_input(&n1, &n2);
   // n1 = 99999, n2 = 99999;

   long long p = 0;

   size_t dim1 = floor(log10(llabs(n1)))+1;
   size_t dim2 = floor(log10(llabs(n2)))+1;

   check_sizes(&dim1, &dim2);

   int* sum = (int*)malloc(sizeof(int) * (dim1+dim2));

   int* s1 = (int*)malloc(sizeof(int) * dim1);
   R_number_to_digits(n1, s1, dim1);

   int* s2 = (int*)malloc(sizeof(int) * dim2);
   R_number_to_digits(n2, s2, dim2);

   print_digits("s1 - input: ", s1, dim1);
   print_digits("s2 - input: ", s2, dim2);

   // main function
   K_multip(sum, s1, dim1, s2, dim2);

   
   printf("--------------------\n");
   for (size_t i = 0; i < (dim1+dim2); i++)
      printf("sum: %d\n", sum[i]);

   for (size_t i = 0; i < (dim1+dim2); i++)
      p += (sum[i] * (long long)pow(10,(double)i));
   
   
   printf("--------------------\n");
   printf("Result:      %lld\n", p);
   printf("Correct:     %lld\n", n1*n2);
   printf("Difference:  %lld\n", (n1*n2) - p);
   printf("--------------------\n");

   free(s1);
   free(s2);
   free(sum);
   return 0;
}