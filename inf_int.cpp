//
// Created by Myeongwon Choi on 01/10/2019.
//

#include "inf_int.h"

/*
 * operator ==
 * implemented by oop class default
 * returns whether or not both are equal
 * operands: two infinite integer
 * return value: true if they are identical, false if they are different
 */
bool operator==(const inf_int &a, const inf_int &b) {
    // we assume 0 is always positive.
    // simplified by Myeongwon Choi
    return (strcmp(a.digits, b.digits) == 0) && a.thesign == b.thesign;
}

/*
 * constructor for integer
 * implemented by Myeongwon Choi
 * set value and the sign to the integer provided
 * param: integer value
 */
inf_int::inf_int(int value) {
    length = 0;
    digits = (char *) malloc(sizeof(char) * 11);
    thesign = value >= 0; // set sign
    value = abs(value); // set value to positive integer

    int i = 0;
    do {
        digits[i++] = '0' + (char) (value % 10); // save the digit to the field
        value = value / 10; // load the next digit
        length++; // count length
    } while (value > 0);
    digits[i] = 0;
}

/*
 * operator << for ostream
 * implemented by Myeongwon Choi
 * return output stream which prints out the number
 */
ostream &operator<<(ostream &os, const inf_int &value) {
    os << (value.thesign ? "" : "-");
    for (int i = value.length - 1; i >= 0; i--) {
        os << value.digits[i];
    }

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

/*
 * operator !=
 * implemented by oop Myeongwon Choi
 * returns whether or not both are different
 * operands: two infinite integer
 * return value: false if they are identical, true if they are different
 */
bool operator!=(const inf_int &a, const inf_int &b) {
    return a != b;
}

/*
 * copy constructor
 * implemented by Myeongwon Choi
 * set value and the sign with existing instance
 * param: one infinite integer
 */
inf_int::inf_int(const inf_int &existing) {
    *this = existing;
}

/*
 * assignment operator =
 * implemented by Myeongwon Choi
 * assign right-hand value to left-hand value
 * lvalue: infinite integer to replace
 * rvalue: infinite integer to assign
 */
inf_int &inf_int::operator=(const inf_int &assignment) {
    length = assignment.length;
    thesign = assignment.thesign;
    digits = (char *) malloc(sizeof(char) * assignment.length + 1);
    strcpy(digits, assignment.digits);
    return *this;
}

/*
 * comparison operator >
 * implemented by Myeongwon Choi
 * compare two values
 */
bool operator>(const inf_int &a, const inf_int &b) {
    bool flag = false;
    if (a == b) return false; //equal
    if (a.thesign != b.thesign) return a.thesign; //sign different

    if (a.length != b.length) { //length different
        flag = a.length > b.length;
    } else { //sign, length equal
        for (int i = a.length - 1; i >= 0; i--) {
            if (a.digits[i] != b.digits[i]) {
                flag = a.digits > b.digits;
                break;
            }
        }
    }
    return a.thesign == flag;
}

/*
 * comparison operator <
 * implemented by Myeongwon Choi
 * compare two values
 */
bool operator<(const inf_int &a, const inf_int &b) {
    if (a == b) return false; //equal
    return !(a > b);
}
