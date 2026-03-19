#include <iostream>
#include <cstring>
#include "swap.h"

typedef unsigned char byte;

void rotate(int a[], int n) {
    int x = a[0];
    for (int i = 1; i < n; i++)
        a[i - 1] = a[i];
    a[n - 1] = x;
}

void string_copy(char* d, char* s) {
    while (*s) {
        *d = *s;
        d++;
        s++;
    }
    *d = '\0'; // добавляем завершающий нуль
}

int len(const char* s) {
    int length = 0;
    while (*s) {
        length++;
        s++;
    }
    return length;
}

int compare(const char* s, const char* t) {
    while (*s && *t && *s == *t) {
        s++;
        t++;
    }
    return *s - *t;
}

int main()
{
    //task 1
    int x = 3;
    int* p = &x;

    std::cout << x << ' ' << *p << ' ' << p << std::endl;
    p++; std::cout << p << std::endl;
    std::cout << p - &x << std::endl;

    //task 2
    byte* pb = (byte*)--p;
    for (byte* pt = pb; pt - pb < sizeof(int); pt++) std::cout << (int)*pt << ' ';
    std::cout << std::endl;

    //task 3
    int f = 3, c = 5;
    std::cout << f << ' ' << c << std::endl;
    swap(&f, &c);
    std::cout << f << ' ' << c << std::endl;

    //task 4
    int a[5]{ 1,2,3,4,5 };
    for (int i = 0; i < 5; i++)
        std::cout << a[i] << ' ';
    std::cout << std::endl;

    for (int* p = a; p - a < 5; p++)
        std::cout << *p << ' ';
    std::cout << std::endl;

    rotate(a, 2);

    //task 5
    char str[] = "Hello!";
    std::cout << str << std::endl;
    std::cout << strlen(str) << ' ' << sizeof(str) << std::endl;

    char t[32];
    for (char* pd = t, *ps = str; *pd++ = *ps++;);

    char u[32];
    string_copy(u, str);
    std::cout << u << std::endl;

    std::cout << len(str) << std::endl;

    const char* s1 = "abc";
    const char* s2 = "abd";
    int cmp = compare(s1, s2);
    std::cout << s1 << " and " << s2 << ": " << cmp << std::endl;

    return 0;
}