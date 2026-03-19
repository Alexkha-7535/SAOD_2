#include <iostream>
#include "Complex.h"


int main() {
    //  task 2
    std::cout << "TASK 2-3" << std::endl;
    Complex c;
    std::cout << "c = " << c << std::endl;

    // task 4
    std::cout << "TASK 4" << std::endl;
    Complex a(1, 2);
    Complex b = 3;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;

    // task 5
    std::cout << "TASK 5" << std::endl;
    Complex x(2, 3);
    Complex y(1, 4);

    Complex sum = x + y;
    Complex diff = x - y;
    Complex prod = x * y;
    Complex quot = x / y;

    std::cout << "x = " << x << ", y = " << y << std::endl;
    std::cout << "x + y = " << sum << std::endl;
    std::cout << "x - y = " << diff << std::endl;
    std::cout << "x * y = " << prod << std::endl;
    std::cout << "x / y = " << quot << std::endl;

    Complex zero = x - x;
    Complex one = x / x;
    std::cout << "x - x = " << zero << " (must be 0)" << std::endl;
    std::cout << "x / x = " << one << " (must be 1)" << std::endl;

    Complex conj = x.Conjugate();
    std::cout << x << " = " << conj << std::endl;

    // task 6
    std::cout << "TASK 6" << std::endl;
    Complex z(3, 4);
    std::cout << "z = " << z << std::endl;
    std::cout << "|z| = " << z.Mod() << std::endl;
    std::cout << "arg(z) = " << z.Arg() << std::endl;

    // task 7
    std::cout << "TASK 7" << std::endl;

    Complex arr1[4];
    std::cout << "array 1" << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << arr1[i] << " ";
    }
    std::cout << std::endl;

    Complex arr2[4] = { 1, 2, Complex(2, 3) };
    std::cout << "array 2" << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << arr2[i] << " ";
    }
    std::cout << std::endl;

    // task 8
    std::cout << "TASK 8" << std::endl;

    Complex* pc = new Complex(5, 6);
    std::cout << "*pc = " << *pc << std::endl;
    std::cout << "pc->Re = " << pc->Re << ", pc->Im = " << pc->Im << std::endl;
    delete pc;

    // 8f-8h: Массив объектов
    Complex* arrPtr = new Complex[3];

    // Заполнение массива
    arrPtr[0] = Complex(1, 1);
    arrPtr[1] = Complex(2, 2);
    arrPtr[2] = Complex(3, 3);

    std::cout << "dynamic array" << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << arrPtr[i] << " ";
    }
    std::cout << std::endl;

    // Демонстрация pc[1].Re
    std::cout << "arrPtr[1].Re = " << arrPtr[1].Re << std::endl;

    delete[] arrPtr;

    return 0;
}