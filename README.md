# Karatsuba's Multiplication

Karatsuba's Multiplication Method

God blessed then and said:
"Be fruitful and MULTIPLY..." - Genesis 1:22


## Main Functions

* ### void K_core(int* , int* , size_t , int* , size_t )
Function where multiplication is performed

## Support functions

* ### void sum_digits(int* ,int* ,size_t )
Function that adds the values,in digits, of two arrays and stores them in the first.

* ### void carry_over_digits(int* ,size_t )
Function that manages the carryovers in the digits array.
This function does not manage the carryover to the most significant digit of the entire array,
because it should be stored outside the size of the array itself.

* ### void check_sizes(size_t*, size_t*)
Function that control if sizes is power of 2 and if not,it adds +1 several times until it reaches the correct size.

* ### void number_to_digits(int ,int* ,size_t )
Function that takes a number, converts it to digits and stores it in an array.
The most significant digit occupies the first position of the array.

* ### void R_number_to_digits(int ,int* ,size_t )
Function that takes a number, converts it to digits and stores it in an array.
The least significant digit occupies the first position of the array.

* ### void K_multip(int*, int* ,size_t ,int* ,size_t )
Function that convert two numbers in two array of digits, call k-core func, and sum final array of digits in result number.

## Range of Number
* Numbers with 1 digit: 1-9 
* Numbers with 2 digits: 10-99
* Numbers with 3 digits: 100-999
* Numbers with 4 digits: 1000-9999 (~Limit of INT value type)
* Numbers with 5 digits: 10000-9999