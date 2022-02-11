// cSpell: Disable
// God blessed then and said:
// "Be fruitful and MULTIPLY..." - Genesis 1:22

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function that converts a number in digits and store in split (less sign. digit -> less sign. posizion)
void R_number_to_digits(int n, int *s, int dim) {
   for (size_t i = 0; i < dim; i++)
   {
      *(s+i) = n%10;
      n /= 10;
   }
}

// Function that converts a number in digits and store in a split (more sign. digit -> less sign. posizion)
void number_to_digits(int n, int *s, int dim) {
   for (size_t i = dim; i-- > 0; )
   {
      *(s+i) = n%10;
      n /= 10;
   }
}

// Function that prints digits in a split
void print_digits(int *s, int dim) {
   for (size_t i = 0; i < dim; i++)
   {
      printf("pos %zu: %d\n", i, *(s+i));
   }
   printf("\n");
}

// Function that reduces number in a split (2+ digits) in digits on the same split
// - It takes into account the carry-overs given by the sum
void carry_over_digits(int *s, int dim) {
   for (size_t i = 0; i < dim; i++) {
      int dimN = floor(log10(abs(s[i])))+1;
      if (dimN != 1) {
         int r = *(s+i)%10;
         int d = *(s+i)/10;
         *(s+i) = r;
         *(s+(i+1)) += d;
      }
   }
}

// Function that sums digits value from 2 splits and store in the first one
void sum_digits(int *s1, int *s2, int dim) {
   // FIXME: +=: a livello di bit all'interno di un 'int' per *s non viene sovrascritto il valore
   //             ma shiftato a destra per ogni somma.
   // *s risulta 2,8,16,10,1,4,8,5
   for (size_t i = 0; i < dim; i++)
      *(s1+i) += *(s2+i);
   
   // FIXME: errore here add 1 in pos 4
   printf("s1 in: \n");
   print_digits(s1, dim*2);

   carry_over_digits(s1, dim);
}

// K-Multiplication of 2/1 digits in splits
void K_multip_2dig(int *sum, int *s1, int dim1, int *s2, int dim2)
{
   *(sum) = *s1 * *s2;
   *(sum+1) = ( *(s1) * *(s2+ dim2 -1) ) + ( *(s1+ dim1 -1) * *(s2) );
   *(sum+2) = *(s1+ dim1 -1) * *(s2+ dim2 -1);
   *(sum+3) = 0;

   carry_over_digits(sum, dim1+dim2);
}

// K-Multiplication of 4/3, 2/1 digits in splits
// TODO: incorret value of second more sign. digit in 'sum', for 4 digits sum;
void K_multip(int *sum, int *s1, int dim1, int *s2, int dim2) {
   if (dim1 != 2 && dim2 != 2) {
      K_multip(sum, s1, dim1/2, s2, dim2/2);

      K_multip(&sum[dim1/2+dim2/2], &s1[dim1/2], dim1-dim1/2, &s2[dim2/2], dim2-dim2/2);

      int* sumapp = (int*)malloc(sizeof(int) * dim1);
      int* sumapp1 = (int*)malloc(sizeof(int) * dim1);

      K_multip(sumapp, s1, dim1/2, &s2[dim2/2], dim2-dim2/2);

      printf("sumapp\n");
      print_digits(sumapp, dim1+1);

      K_multip(sumapp1, &s1[dim1/2], dim1-dim1/2, s2, dim2/2);

      // TODO: Provare a sommare 0 prima di sommare in sumapp
      // TODO: Provare con array normali, ma non si puo modificare la lunghezza a runtime
      printf("sumapp1\n");
      print_digits(sumapp1, dim1);

      // FIXME: 5th digit wrong, in sum_digits
      sum_digits(sumapp, sumapp1, dim1+1);

      printf("sumapp sum \n");
      print_digits(sumapp, dim1+1);

      printf("sum \n");
      print_digits(sum, dim1+dim2);

      sum_digits(&sum[(dim1+dim2)/4], sumapp, dim1+1);

      free(sumapp);
      free(sumapp1);
   } else K_multip_2dig(sum, s1, dim1, s2, dim2);
}

// Function that receves input numbers from user
void user_input(int* n1, int* n2) {
   printf("Insert first number (range ~1000 - 100 ; 99 - 10 ; 9 - 1): ");
   scanf("%d", n1);
   printf("Insert second number (range ~1000 - 100 ; 99 - 10 ; 9 - 1): ");
   scanf("%d", n2);
}

// TODO: change type of ALL number and digits in uint32_t?(per aumentare il numero massimo possibile)
// size_t, long long int, int32_t, uint32_t, int64_t, uint64_t, intmax_t

int main() {
   int n1,n2;
   
   // user_input(&n1, &n2);
   n1 = 5999, n2 = 5999;

   int p = 0;

   int dim1 = floor(log10(abs(n1)))+1;
   int dim2 = floor(log10(abs(n2)))+1;

   if (dim1%2 != 0) {
      dim1 += 1;
   }
   if (dim2%2 != 0) {
      dim2 += 1;
   }

   int* sum = (int*)malloc(sizeof(int) * (dim1+dim2));

   int* s1 = (int*)malloc(sizeof(int) * dim1);
   R_number_to_digits(n1, s1, dim1);

   int* s2 = (int*)malloc(sizeof(int) * dim2);
   R_number_to_digits(n2, s2, dim2);

   // main function
   K_multip(sum, s1, dim1, s2, dim2);

   
   printf("--------------------\n");
   for (int i = 0; i < (dim1+dim2); i++)
   {
      printf("sum: %d\n", sum[i]);
   }
   printf("--------------------\n");

   for (int i = 0; i < (dim1+dim2); i++)
   {
      p += (sum[i] * (int)pow(10,(double)i));
   }
   
   printf("Result:      %d\n", p);
   printf("Correct:     %d\n", n1*n2);
   printf("Difference:  %d\n", (n1*n2) - p);
   printf("--------------------\n");

   free(s1);
   free(s2);
   free(sum);
   return 0;
}