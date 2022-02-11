# Karatusaba's Multiplication

Karatusaba's Multiplication Method

God blessed then and said:
"Be fruitful and MULTIPLY..." - Genesis 1:22


## Main Functions

* ### void K_Multip(int* ,int* ,int ,int )
* ### void K_Multip_2digit(int* ,int* , int ,int* ,int )

## Support functions

* ### void sum_digits(int* ,int* ,int )
Function that receive 2 'array' of digits, and sum second array into first array.

* ### void carry_over_digits(int* ,int )
Function that receive an 'array' after-sum and reduce all values in digit.
WARNING: This function has a bug: remove carry-over of more significant digits.

* ### void number_to_digits(int ,int* ,int )
Function that receive a number and convert it in an 'array' of digits, with more significant digit on first position.

* ### void R_number_to_digits(int ,int* ,int )
Function that receive a number and convert it in an 'array' of digits, with less significant digit on first position.

## Range of Number
* numbers with 1 digit: 1-9 
* numbers with 2 digits: 10-99
* numbers with 3 digits: 100-999