#ifndef _K_Multip_h
#define _K_Multip_h

/**
 * Function that takes a number, converts it to digits and stores it in an array.
 * The least significant digit occupies the first position of the array.
 * */
void R_number_to_digits(int n, int *s, size_t dim);

/**
 * Function that takes a number, converts it to digits and stores it in an array.
 * The most significant digit occupies the first position of the array.
 * */
void number_to_digits(int n, int *s, size_t dim);

/**
 * Function that control if sizes is power of 2 and if not, it adds +1 several times until it reaches the correct size.
 * */
void check_sizes(size_t* ptr1, size_t* ptr2);

/**
 * Function that manages the carryovers in the digits array.
 * This function does not manage the carryover to the most significant digit of the entire array,
 * because it should be stored outside the size of the array itself.
 * */
void carry_over_to_digits(int *s, size_t dim);

/**
 * Function that adds the values,in digits, of two arrays and stores them in the first.
 * */
void sum_digits(int *s1, int *s2, size_t dim);

/**
 * Function where multiplication is performed
 * */
void K_core(int* sum, int* s1, size_t dim1, int* s2, size_t dim2);

/**
 * Function that convert two numbers in two array of digits, call k-core func, and sum final array of digits in result number.
 * */
long long K_multip(long long a, long long b);

#endif