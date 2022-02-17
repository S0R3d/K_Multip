# Karatsuba's Multiplication

Karatsuba's Multiplication Method

God blessed then and said:
"Be fruitful and MULTIPLY..." - Genesis 1:22


## Main Functions

* ### void K_Multip(int*, int* ,size_t ,int* ,size_t )

## Support functions

* ### void sum_digits(int* ,int* ,size_t )
Function that receive 2 'array' of digits, and sum second array into first array.

* ### void carry_over_digits(int* ,size_t )
Function that receive an 'array' after-sum and reduce all values in digit.

* ### void check_sizes(size_t*, size_t*)
Function that receive 2 pointers of int(dimension) and checks if these dimensions are correct, otherwise change them.

* ### void number_to_digits(int ,int* ,size_t )
Function that receive a number and convert it in an 'array' of digits, with more significant digit on first position.

* ### void R_number_to_digits(int ,int* ,size_t )
Function that receive a number and convert it in an 'array' of digits, with less significant digit on first position.

## Range of Number
* Numbers with 1 digit: 1-9 
* Numbers with 2 digits: 10-99
* Numbers with 3 digits: 100-999
* Numbers with 4 digits: 1000-9999 (~Limit of INT value type)
* Numbers with 5 digits: 10000-9999