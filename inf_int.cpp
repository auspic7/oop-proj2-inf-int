//
// Created by Myeongwon Choi on 01/10/2019.
//

#include "inf_int.h"

/*
 * operator ==
 * implemented by oop class default
 * returns whether or not both are different
 * operands: two infinite integer
 * return value: true if they are identical, false if they are different
 */
bool operator==(const inf_int& a , const inf_int& b)
{
    // we assume 0 is always positive.
    // simplified by Myeongwon Choi
    return (strcmp(a.digits , b.digits) == 0) && a.thesign == b.thesign;
}

/*
 * constructor for integer
 * implemented by Myeongwon Choi
 * set value and the sign to the integer provided
 * param: integer value
 */
inf_int::inf_int(int value) {
    length = 0;
    digits = (char *)malloc(sizeof(char) * 11);
    thesign = value >= 0; // set sign
    value = abs(value); // set value to positive integer

    int i = 0;
    do{
        digits[i++] = '0' + (char)(value%10); // save the digit to the field
        value = value/10; // load the next digit
        length++; // count length
    }
    while(value > 0);
    digits[i] = 0;
}

/*
 * operator << for ostream
 * implemented by Myeongwon Choi
 * return output stream which prints out the number
 */
ostream &operator<<(ostream & os, const inf_int & value) {
    std::string s;
    for (int i = value.length -1; i >= 0; i--){
        s += value.digits[i];
    }
    os << (value.thesign?"":"-") << s;

    return os;
}

/*
 * destructor
 * implemented by Myeongwon Choi
 * make dynamically allocated memory space free
 */
inf_int::~inf_int() {
    free(digits);
}

/*
 * default constructor
 * implemented by Myeongwon Choi
 * set value and the sign to zero
 * param: none
 */
inf_int::inf_int() : inf_int(0) {}

bool operator!=(const inf_int &a, const inf_int &b) {
    return a!=b;
}


