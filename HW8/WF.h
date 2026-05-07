#ifndef WF_H
#define WF_H

#include <string>
#include <stdexcept>
#include <algorithm>
#include <iostream>

class WF {
private:
    int* pm = nullptr;
    int M = 0, N = 0; // M = rows, N = cols
    std::string s, t;

    void freeMemory() {
        delete[] pm;
        pm = nullptr;
        M = N = 0;
    }

    int idx(int i, int j) const { return i * N + j; }

public:
    WF() = default;
    ~WF() { freeMemory(); }

    // 11. Запрет копирования и присваивания
    WF(const WF&) = delete;
    WF& operator=(const WF&) = delete;

    void Init(const char* sc, const char* tc) {
        freeMemory(); // Решаем проблему утечки при повторной инициализации
        s = sc; t = tc;
        M = s.length() + 1;
        N = t.length() + 1;
        pm = new int[M * N];

        // Инициализация первой строки и столбца
        for (int i = 0; i < M; ++i) pm[idx(i, 0)] = i;
        for (int j = 0; j < N; ++j) pm[idx(0, j)] = j;

        // Алгоритм Вагнера-Фишера
        for (int i = 1; i < M; ++i) {
            for (int j = 1; j < N; ++j) {
                int cost = (s[i-1] == t[j-1]) ? 0 : 1;
                pm[idx(i, j)] = std::min({
                    pm[idx(i-1, j)] + 1,      // удаление
                    pm[idx(i, j-1)] + 1,      // вставка
                    pm[idx(i-1, j-1)] + cost  // замена
                });
            }
        }
    }

    int Rows() const { return M; }
    int Columns() const { return N; }

    int Get(int i, int j) const {
        if (i < 0 || i >= M || j < 0 || j >= N)
            throw std::out_of_range("Get: Index out of range");
        return pm[idx(i, j)];
    }

    void Set(int i, int j, int val) {
        if (i < 0 || i >= M || j < 0 || j >= N)
            throw std::out_of_range("Set: Index out of range");
        pm[idx(i, j)] = val;
    }

    int Distance() const {
        return (M > 0 && N > 0) ? pm[idx(M-1, N-1)] : 0;
    }
};
#endif // WF_H