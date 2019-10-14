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

//TODO: finish implementation
inf_int operator+(const inf_int &a, const inf_int &b) {
    inf_int c;
    unsigned int i;

    if (a.thesign == b.thesign) {   // 이항의 부호가 같을 경우 + 연산자로 연산
        for (i = 0; i < a.length; i++) {
            c.Add(a.digits[i], i + 1);
        }
        for (i = 0; i < b.length; i++) {
            c.Add(b.digits[i], i + 1);
        }

        c.thesign = a.thesign;

        return c;
    } else {   // 이항의 부호가 다를 경우 - 연산자로 연산
        c = b;
        c.thesign = a.thesign;

        return a - c;
    }
}


inf_int operator-(const inf_int &a, const inf_int &b) {
    inf_int c;
    unsigned int i;

    if (a > b) {
        if (a.thesign == b.thesign) {
            if (a.thesign) {
                for (i = 0; i < a.length; i++) {
                    c.Add(a.digits[i], i + 1);
                }
                for (i = 0; i < b.length; i++) {
                    c.Sub(b.digits[i], i + 1);
                }
                c.thesign = true;
                return c;
            } else {
                for (i = 0; i < b.length; i++) {
                    c.Add(b.digits[i], i + 1);
                }
                for (i = 0; i < a.length; i++) {
                    c.Sub(a.digits[i], i + 1);
                }
                c.thesign = true;
                return c;
            }
        } else {
            c = b;
            c.thesign = a.thesign;
            return a + c;
        }
    } else {
        if (a.thesign == b.thesign) {
            if (a.thesign) {

                for (i = 0; i < b.length; i++) {
                    c.Add(b.digits[i], i + 1);
                }
                for (i = 0; i < a.length; i++) {
                    c.Sub(a.digits[i], i + 1);
                }
                c.thesign = false;
                return c;

            } else {
                for (i = 0; i < a.length; i++) {
                    c.Add(a.digits[i], i + 1);
                }
                for (i = 0; i < b.length; i++) {
                    c.Sub(b.digits[i], i + 1);
                }
                c.thesign = false;
                return c;
            }
        } else {
            c = b;
            c.thesign = a.thesign;
            return a + c;

        }
    }
    // to be filled
}


inf_int operator*(const inf_int &a, const inf_int &b) {
    inf_int c;
    inf_int d;
    unsigned int i, j, k;
    c.length = a.length + b.length;
    c.digits = (char *) realloc(c.digits, c.length + 1);
    c.digits[c.length] = '\0';

    for (i = 0; i < c.length; i++) {
        c.digits[i] = 0;
    }

    for (i = 0; i < a.length; i++) {
        for (j = 0; j < b.length; j++) {
            k = i + j;
            c.Mul(a.digits[i], b.digits[j], k + 1);
        }
    }
    if (a.thesign == b.thesign) {
        c.thesign = true;
    } else
        c.thesign = false;

    for (i = 0; i < c.length; i++) {
        c.digits[i] += '0';
    }

    if (c.length > 1 && c.digits[c.length - 1] == '0') {
        d.digits = (char *) realloc(d.digits, c.length);
        d.length = c.length - 1;
        d.digits[d.length] = '\0';
        for (i = 0; i < c.length; i++) {
            d.digits[i] = 0;
        }
        for (i = 0; i < d.length; i++) {
            d.digits[i] += c.digits[i];
        }
        d.thesign = c.thesign;
        return d;
    } else
        return c;


}


void inf_int::Add(const char num,
                  const unsigned int index)   // a의 index 자리수에 n을 더한다. 0<=n<=9, ex) a가 391일때, Add(a, 2, 2)의 결과는 411
{
    if (this->length < index) {
        this->digits = (char *) realloc(this->digits, index + 1);

        if (this->digits == NULL) {      // 할당 실패 예외처리
            cout << "Memory reallocation failed, the program will terminate." << endl;

            exit(0);
        }

        this->length = index;               // 길이 지정
        this->digits[this->length] = '\0';   // 널문자 삽입
    }

    if (this->digits[index - 1] < '0') {   // 연산 전에 '0'보다 작은 아스키값인 경우 0으로 채움. 쓰여지지 않았던 새로운 자리수일 경우 발생
        this->digits[index - 1] = '0';
    }

    this->digits[index - 1] += num - '0';   // 값 연산


    if (this->digits[index - 1] > '9') {   // 자리올림이 발생할 경우
        this->digits[index - 1] -= 10;   // 현재 자릿수에서 (아스키값) 10을 빼고
        Add('1', index + 1);         // 윗자리에 1을 더한다
    }
}

void inf_int::Sub(const char num, const unsigned int index) {

    this->digits[index - 1] -= num - '0';

    if (this->digits[index - 1] < '0') {
        this->digits[index - 1] += 10;
        Sub('1', index + 1);
    }
}

void inf_int::Mul(const char a, const char b, const unsigned int index) {

    this->digits[index - 1] += (a - '0') * (b - '0');
    if (this->digits[index - 1] > 9) {
        this->digits[index] += this->digits[index - 1] / 10;
        this->digits[index - 1] %= 10;
    }

}

inf_int::inf_int(const char *str) {
    if (str[0] == '-') {
        this->thesign = false;
        this->length = strlen(str) - 1;
        this->digits = new char[length + 1];
        for (int i = 0; i < length; i++) {
            this->digits[i] = str[this->length - i];
        }
        this->digits[length] = '\0';
    } else {
        this->thesign = true;
        if (str[0] == '+') {
            this->length = strlen(str) - 1;
            this->digits = new char[length + 1];
            for (int i = 0; i < length; i++) {
                this->digits[i] = str[this->length - i];
            }
            this->digits[length] = '\0';
        } else {
            this->length = strlen(str);
            this->digits = new char[length + 1];
            for (int i = 0; i < length; i++) {
                this->digits[i] = str[this->length - 1 - i];
            }
            this->digits[length] = '\0';
        }
    }
}

