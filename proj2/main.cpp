#include <iostream>
#include "inf_int.h"
#include "inf_int.cpp"

using namespace std;

int main() {
    inf_int a, e;
    inf_int b(100);
    inf_int c("321111111111122222222222233333333333444444444445555555555");
    inf_int d("123451987651234572749499923455022211");
    inf_int f=d;
    inf_int g(f);

    // cin >> g ;   // not required

    // a=b*c;
    // e=g/f;       // not required

    b=c-d;
    cout << b;
    return 0;
}