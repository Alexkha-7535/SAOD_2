#include <iostream>
#include "WF.h"
#include "WFOpt.h"

int main() {
    std::cout << "=== Часть 1: Класс WF ===\n";
    WF wf;
    wf.Init("no", "ono");

    std::cout << "Матрица расстояний:\n";
    for (int i = 0; i < wf.Rows(); ++i) {
        for (int j = 0; j < wf.Columns(); ++j)
            std::cout << wf.Get(i, j) << "\t";
        std::cout << "\n";
    }
    std::cout << "Расстояние (WF): " << wf.Distance() << "\n\n";

    // 10. Проверка свойств метрики
    auto d = [](const char* a, const char* b) { WF w; w.Init(a,b); return w.Distance(); };
    std::cout << "Проверка метрики:\n";
    std::cout << "1. Неотрицательность: " << (d("a","b") >= 0 ? "OK" : "FAIL") << "\n";
    std::cout << "2. Тождество: d(x,x)=0 -> " << (d("test","test") == 0 ? "OK" : "FAIL") << "\n";
    std::cout << "3. Симметрия: d(x,y)=d(y,x) -> " << (d("abc","cba") == d("cba","abc") ? "OK" : "FAIL") << "\n";
    int d_ab = d("kitten", "sitting");
    int d_bc = d("sitting", "sitted");
    int d_ac = d("kitten", "sitted");
    std::cout << "4. Треугольник: d(a,c) <= d(a,b)+d(b,c) -> " << (d_ac <= d_ab + d_bc ? "OK" : "FAIL") << "\n\n";

    // Тест с N=2 (по запросу)
    std::cout << "=== Тест для N=2 (строки 'ab', 'cd') ===\n";
    WF wf2; wf2.Init("ab", "cd");
    std::cout << "WF Distance: " << wf2.Distance() << "\n";
    std::cout << "Opt Distance: " << Distance("ab", "cd") << "\n\n";

    std::cout << "=== Часть 2: Оптимизированный Distance ===\n";
    int d_opt = Distance("no", "ono");
    std::cout << "Расстояние (Opt): " << d_opt << "\n";
    std::cout << "Совпадение с WF: " << (d_opt == wf.Distance() ? "OK" : "FAIL") << "\n";

    return 0;
}