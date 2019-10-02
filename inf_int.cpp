//
// Created by Myeongwon Choi on 01/10/2019.
//

#include "inf_int.h"
#include <cstdlib>

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
    thesign = value >= 0; // set sign
    value = abs(value); // set value to positive integer

    int i = 0;
    do{
        digits[i] = '0' + (char)(value%10);
        value = value/10;
    }
    while(value > 0);

}

/*
 * operator << for ostream
 * implemented by Myeongwon Choi
 * return output stream
 */
ostream &operator<<(ostream & os, const inf_int & value) {
    for (int i = 0; i < value.length; i++){

    }
    os << value.thesign?"":"-" << ;
    return os;
}

