#include <iostream>
using namespace std;
int Plus(int a, int b) { return a + b; }

int main()
{
    //task1
    cout << "Hellow World!" << endl << endl;

    //task2
    int x, y;

    cout << "x = ? ";
    cin >> x;

    cout << "y = ? ";
    cin >> y;

    cout << x << " + " << y << " = " << x + y << endl;
    cout << x << " - " << y << " = " << x - y << endl;
    cout << x << " * " << y << " = " << x * y << endl;
    cout << x << " / " << y << " = " << x / y << endl;
    cout << x << " % " << y << " = " << x % y << endl;
    cout << x << " | " << y << " = " << (x | y) << endl;
    cout << x << " & " << y << " = " << (x & y) << endl;
    cout << x << " ^ " << y << " = " << (x ^ y) << endl;
    cout << x << " << " << y << " = " << (x << y) << endl;
    cout << x << " >> " << y << " = " << (x >> y) << endl << endl;

    //task3
    x = 3, y = 5;

    cout << "x + y = " << Plus(x, y) << endl;

    return 0;
}