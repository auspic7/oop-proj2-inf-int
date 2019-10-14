#include "inf_int.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>

using namespace std;

int main()
{
    inf_int a(23456789), b(
            "15423897234594523345297534798234567897853427872890379823459782345978324234597825349787896345789634526789"), c(
            -1), d("154238972345945233452975347982345678978");

    cout << (a > b) << (b > d) << (a > c) << endl << a * b;
    /*
    inf_int a, e;
    inf_int b(100);
    inf_int c("321111111111122222222222233333333333444444444445555555555");
    inf_int d("123451987651234572749499923455022211");
    inf_int f=d;
    inf_int g(f);

    // cin >> g ;   // not required

    a=b*c;
    // e=g/f;       // not required

    b=c-d;


    if (f==d) {
        cout << "a : " << a << endl;
        cout << "b : " << b << endl;
        cout << "c : " << c << endl;
        cout << "d : " << d << endl;
        // cout << "e : " << e << endl;
        cout << "f : " << f << endl;
        // cout << "g : " << g << endl;
    }
     */

    return 0;
}
