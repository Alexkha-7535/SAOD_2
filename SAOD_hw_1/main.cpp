#include <iostream>

int Plus(int a, int b) {return a + b;}

int main()
{
    //task 1
    std::cout << "Hello world" << std::endl;

    //task 2
    int x, y;
    std::cout << "x = ? "; std::cin >> x; // Подсказка и ввод х
    std::cout << "y = ? "; std::cin >> y; // Подсказка и ввод y
    std::cout << x << " + " << y << " = " << x + y << std::endl;
    std::cout << x << " * " << y << " = " << x * y << std::endl;
    std::cout << x << " / " << y << " = " << x / y << std::endl;
    std::cout << x << " % " << y << " = " << x % y << std::endl;
    std::cout << x << " & " << y << " = " << (x & y) << std::endl;
    std::cout << x << " | " << y << " = " << (x | y) << std::endl;

    //task 3
    x = 3, y = 5;
    std::cout << x+y << std::endl;
    std::cout << Plus (x, y) << std::endl;
    return 0;
}