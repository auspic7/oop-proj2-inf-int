//
// Created by Myeongwon Choi on 01/10/2019.
//

#include "inf_int.h"

/*
 * function abs
 * implemented by Myeongwon Choi
 * returns positive-signed infinite integer
 * parameter: one infinite integer
 * return value: positive-signed infinite integer
 */
inf_int abs(const inf_int &a) {
    inf_int res(a);
    res.thesign = true;
    return res;
}

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
 * implemented by Seungjin Lee
 * return output stream which prints out the number
 */
ostream& operator<<(ostream &os, const inf_int &result) {

    // if thesign is true(positive-#) "" will print,
    // thesign is false(negative-#) "-" will print.
    if(result.thesign == false)
        os << '-';
    os << result.digits;
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
 * constructor
 * implemented by Seungjin Lee
 * set value if input is char pointer param
 * param : const char*
 */
inf_int::inf_int(const char* tmp) {

    int cnt = 0;
    // if tmp has no value
    if ((int)strlen(tmp) == 1 && tmp[0]== '0') {
        digits = new char[1];
        digits[0] = '0';
        digits[1] = '\0';
    }
        // if tmp sign is negative
    else if(tmp[0] == '-') {
        thesign = false;
        cnt = 1;
        for (int i = 1; ;i++) {
            if(tmp[i] != '0') break;
            cnt++;
        }

        digits = new char[(int)strlen(tmp) - cnt];
        for (int i = 0; i<(int)strlen(tmp) - cnt; i++) {
            digits[i] = tmp[i+cnt];
        }
        // rightmost index must be NULL
        digits[(int)strlen(tmp) - cnt] = '\0';
        length = (int)strlen(digits);
    } // if tmp sign is positive
    else {
        thesign = true;
        for (int i = 1; ;i++) {
            if(tmp[i] != '0') break;
            cnt++;
        }
        digits = new char[(int)strlen(tmp) - cnt];
        int j = 0;
        for (int i = (int)strlen(tmp)-cnt; i>0; i--) {
            digits[j] = tmp[i];
        }
        for (int i = 0; i<(int)strlen(tmp) - cnt; i++) {
            digits[i] = tmp[i+cnt];
        }
        // rightmost index must be NULL
        digits[(int)strlen(tmp) - cnt] = '\0';
        length = (int)strlen(digits);
    }
}


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
                flag = a.digits[i] > b.digits[i];
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

/*
 * addition operator +
 * implemented by Seungjin Lee
 * add two values
 */
inf_int operator+(const inf_int &a, const inf_int &b) {
    // if thesign is same
    char *high, *low, *tmp, *final;
    int max_i, min_j, carry, temp, len, findex;

    // if the two value has the same sign
    // -,- or +,+
    if(a.thesign == b.thesign) {
        // 길이가 긴 것을 찾기
        if(a.length < b.length) {
            high = new char[(int)strlen(b.digits)];
            low = new char[(int)strlen(a.digits)];
            strcpy(high, b.digits);
            strcpy(low, a.digits);
            max_i = b.length-1;
            min_j = a.length-1;
        }else{
            high = new char[(int)strlen(a.digits)];
            low = new char[(int)strlen(b.digits)];
            strcpy(high,a.digits);
            strcpy(low,b.digits);
            max_i = a.length - 1;
            min_j = b.length - 1;
        }
        // when we add two value, store result in tmp temporary.
        tmp = new char[(int)strlen(high)];
        carry = 0;
        // addition two a, b in min_j length
        // temp is variable that store the result
        // ex : a = 123, b = 4567,
        while(true) {
            // when we add a = 123, b = 4567
            temp = ((int)(high[max_i] - '0') + (int)(low[min_j] - '0'));
            // 1 iteration, a[2 = min_j] (3) + b[3 = max_i] (7) = 10
            temp = temp + carry; // 10 + 0
            if (temp >= 10) {
                carry = 1;
                temp %= 10; // temp = 0
            } else {
                carry = 0;
            }
            tmp[max_i] = temp + '0';
            // tmp[max_i = 3] = 0 is stored.
            max_i--;
            min_j--;
            if(min_j < 0) {
                break;
            }
        }

        // 남은 자리 숫자 더하기
        for( ; max_i >=0; max_i--) {
            temp = (int)(high[max_i] - '0') + carry;
            if (temp >= 10) {
                carry = 1;
                temp = temp % 10; // temp = 0
            } else {
                carry = 0;
            }
            tmp[max_i] = temp + '0';
        }
        tmp[(int)strlen(high)] = '\0';

        // if carry is left. 즉, 마지막까지 올림자리가 남은 경우
        if (carry != 0 ) {
            // if a and b are positive
            if (a.thesign && b.thesign) {
                len = (int) strlen(tmp) + 1;
                findex = 1;
                final = new char[len];
                final[0] = carry + '0';
                for (int k = findex; k < len; k++) {
                    final[k] = tmp[k - 1];
                }
            }
                // a and b are negative
            else if (!a.thesign && !b.thesign) {
                len = (int) strlen(tmp) + 2;
                findex = 2;
                final = new char[len];
                final[0] = '-';
                final[1] = carry + '0';
                for (int k = findex; k < len; k++) {
                    final[k] = tmp[k - 1];
                }
            }
        }else{
            if(a.thesign && b.thesign){ // 둘다 양수라면
                len = (int)strlen(tmp);
                findex = 0;
                final = new char[len];
                for(int k = findex ; k < len ; k++) {
                    final[k] = tmp[k];
                }
            }else if(!a.thesign && !b.thesign){ // 둘다 음수라면
                len = (int)strlen(tmp) + 2;
                findex = 1;
                final = new char[len];
                final[0] = '-'; // 부호 할당
                for(int k = findex ; k < len ; k++) {
                    final[k] = tmp[k-1];
                }
            }
        }
        final[len] = '\0';
        inf_int result(final);
        return result;
    }
        // if two arg sign is different
    else {
        bool sign = true;
        // result sign
        // if two arg digits are same and sign is different each other
        // return 0
        if (!strcmp(a.digits, b.digits)) {
            inf_int result(0);
            return result;
        }
        // if b has negative sign
        if (!b.thesign) {
            if (a.length > b.length) {
                sign = true;
            } else if (a.length < b.length) {
                sign = false;
            } else {
                for (int i = 0; i < a.length; i++) {
                    if ((a.digits[i] - '0') > (b.digits[i] - '0')) {
                        sign = true;
                        break;
                    } else if ((a.digits[i] - '0') < (b.digits[i] - '0')) {
                        sign = false;
                        break;
                    }
                }
            }
            // if sign is true, a is bigger than b
            if (sign) {
                high = new char[(int) strlen(a.digits)];
                low = new char[(int) strlen(b.digits)];
                strcpy(high, a.digits);
                strcpy(low, b.digits);
                max_i = a.length - 1;
                min_j = b.length - 1;
            } else {
                high = new char[(int) strlen(b.digits)];
                low = new char[(int) strlen(a.digits)];
                strcpy(high, b.digits);
                strcpy(low, a.digits);
                max_i = b.length - 1;
                min_j = a.length - 1;
            }
        }
            // if a has negative sign
        else {
            if (a.length > b.length) {
                sign = false;
            } else if (a.length < b.length) {
                sign = true;
            } else {
                for (int i = 0; i < a.length; i++) {
                    if ((a.digits[i] - '0') > (b.digits[i] - '0')) {
                        sign = false;
                        break;
                    } else if ((a.digits[i] - '0') < (b.digits[i] - '0')) {
                        sign = true;
                        break;
                    }
                }
            }
            // if sign is true, b is bigger than a
            if (sign) {
                high = new char[(int) strlen(b.digits)];
                low = new char[(int) strlen(a.digits)];
                strcpy(high, b.digits);
                strcpy(low, a.digits);
                max_i = b.length - 1;
                min_j = a.length - 1;
            } else {
                high = new char[(int) strlen(a.digits)];
                low = new char[(int) strlen(b.digits)];
                strcpy(high, a.digits);
                strcpy(low, b.digits);
                max_i = a.length - 1;
                min_j = b.length - 1;
            }
        }
        tmp = new char[(int)strlen(high)];
        carry = 0;
        while (1) {
            // when we add a = 123, b = 4567
            temp = ((int)(high[max_i] - '0') - (int)(low[min_j] - '0'));
            // 1 iteration, a[2 = min_j] (3) + b[3 = max_i] (7) = 10
            temp = temp - carry; // 10 + 0
            if (temp < 0) {
                carry = 1;
                temp = temp + 10; // temp = 0
            } else {
                carry = 0;
            }
            tmp[max_i] = temp + '0';
            // tmp[max_i = 3] = 0 is stored.
            max_i--;
            min_j--;
            if (min_j < 0) {
                break;
            }
        }

        // 남은 자리 숫자 더하기
        for (; max_i >= 0; max_i--) {
            temp = (int) (high[max_i] - '0') + carry;
            if (temp < 0) {
                carry = 1;
                temp = temp + 10; // temp = 0
            } else {
                carry = 0;
            }
            tmp[max_i] = temp + '0';
        }
        tmp[max_i] = '\0';

        // if carry is left. 즉, 마지막까지 올림자리가 남은 경우
        if (tmp[0] == '0') {
            // if a and b are positive
            if (!sign) {
                len = (int) strlen(tmp);
                final = new char[len];
                final[0] = '-';
                for (int k = 1; k < len; k++) {
                    final[k] = tmp[k];
                }
            }
        } else {
            if (!sign) {
                len = (int) strlen(tmp) + 1;
                final = new char[len];
                final[0] = '-';
                for (int k = 1; k < len; k++) {
                    final[k] = tmp[k - 1];
                }
            } else {
                len = (int) strlen(tmp);
                final = new char[len];
                for (int k = 0; k < len; k++) {
                    final[k] = tmp[k];
                }
            }
        }
        final[len] = '\0';
        inf_int result(final);
        return result;
    }
}

/*
 * subtraction operator -
 * implemented by Seungjin Lee
 * subtract two values
 * using operator +
 */
inf_int operator-(const inf_int &a, const inf_int &b) {
    char *tmp, *result;

    // if sign is different, longer value change the sign and add
    if(a.thesign != b.thesign) {
        // sign is different, digits are same.
        // ex a = 1234, b = -1234
        if(!strcmp(a.digits, b.digits)) {
            inf_int result(0);
            return result;
        }
        // 양수라고 생각하고 더하고, 맨앞에 부호만 붙이면 됨.
        if(!b.thesign) {
            // b's sign is negative (a's sign is positive), negate and add.
            inf_int result(b.digits);
            return a+result;
        } else {
            // b's sign is positive so, a's sign is negative,
            // result must be negative.
            // else means b.thesign is positive. so, neg - pos should be neg.
            tmp = new char[b.length+1];
            tmp[0] = '-';
            for (int i = 1; i<b.length + 1; i++) {
                tmp[i] = b.digits[i-1];
            }
            tmp[b.length+1] = '\0';
            inf_int result(tmp);
            return a+result;
        }
    }else {
        // the sign is same. negate b's sign and add.
        if(!b.thesign) {
            // b's sign is negative, a's sign is negative.
            // neg - neg, so b's sign will change in positive.
            inf_int result(b.digits);
            return a+result;
        } else {
            // a, b sign is positive.
            // pos - pos so, negate b's sign and add.
            tmp = new char[b.length+1];
            tmp[0] = '-';
            for (int i = 1; i<=b.length; i++) {
                tmp[i] = b.digits[i-1];
            }
            tmp[b.length+1] = '\0';
            inf_int result(tmp);
            return a+result;
        }
    }
}

inf_int operator*(const inf_int &a, const inf_int &b) {
    inf_int result, i, temp;
    if (a > b) {
        while (i < b) {
            result = result + a;
            i = i + 1;
        }
    } else {
        while (i < a) {
            result = result + b;
            i = i + 1;
        }
    }

    result.thesign = a.thesign == b.thesign;
    return result;
}
