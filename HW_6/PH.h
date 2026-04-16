#ifndef PH_H
#define PH_H

#include <cstring>
#include <stdexcept>

class PH
{
private:
    static const int k = 257;       // основание > 255, простое
    static const int Q = 65521;     // большое простое число (2^16 - 2^5 + 1)

    int* kp;            // массив степеней k^i % Q
    int L;              // максимальная длина хеширования (длина образца)

    // Приведение к наименьшему неотрицательному остатку
    static int norm(int x) {
        x %= Q;
        if (x < 0) x += Q;
        return x;
    }

public:
    // Конструктор: L — длина фрагмента, для которого будем считать хеш
    PH(int length) : L(length) {
        if (L <= 0) throw std::invalid_argument("Length must be positive");
        // Нужно хранить степени k^0 ... k^L (всего L+1 элементов)
        kp = new int[L + 1];
        kp[0] = 1;
        for (int i = 1; i <= L; ++i) {
            // kp[i] = (kp[i-1] * k) % Q, но с защитой от переполнения
            long long temp = (long long)kp[i-1] * k;
            kp[i] = norm((int)(temp % Q));
        }
    }

    // Деструктор
    ~PH() {
        delete[] kp;
    }

    // Вычисление хеша для строки s (должна быть длиной L)
    int Hash(const char* s) const {
        int h = 0;
        // По формуле (*): H = (s[0]*k^{L-1} + s[1]*k^{L-2} + ... + s[L-1]*k^0) % Q
        // В нашем массиве kp[i] хранит k^i % Q. Нам нужны степени от L-1 до 0.
        for (int i = 0; i < L; ++i) {
            // Используем long long для предотвращения переполнения
            long long term = (long long)(unsigned char)s[i] * kp[L - 1 - i];
            h = norm(h + (int)(term % Q));
        }
        return h;
    }

    // Пересчёт хеша при сдвиге окна на 1 вправо
    // h     — текущий хеш (для фрагмента T[i..i+L-1])
    // pref  — символ, который покидает окно (T[i])
    // suff  — символ, который входит в окно (T[i+L])
    int Shift(int h, char pref, char suff) const {
        // Формула (**):
        // H_new = (k * H_old - pref * k^{L} + suff) % Q
        // Где k^{L} хранится в kp[L]
        long long term = (long long)(unsigned char)pref * kp[L];
        long long new_h = (long long)h * k - term + (unsigned char)suff;
        return norm((int)(new_h % Q));
    }

    // Получить длину (может пригодиться)
    int Length() const { return L; }
};

#endif