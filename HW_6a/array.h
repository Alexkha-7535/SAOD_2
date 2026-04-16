#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <stdexcept>
#include "data.h"

class Array
{
private:
    int m_rows;          // количество строк
    int m_cols;          // количество столбцов
    _data* m_pDataRef;   // указатель на данные с подсчётом ссылок

public:
    // Конструктор: создаёт массив m x n
    Array(int m, int n, int* p = nullptr);
    
    // Конструктор копирования (view — данные не копируются)
    Array(const Array& other);
    
    // Деструктор
    ~Array();
    
    // Оператор присваивания
    Array& operator=(const Array& other);
    
    // Получение размеров
    int Rows() const { return m_rows; }
    int Cols() const { return m_cols; }
    
    // Доступ к элементу (для чтения и записи)
    int& Item(int i, int j);
    
    // Доступ к элементу (только для чтения)
    int Item(int i, int j) const;
    
    // Изменение формы (создаёт новый view)
    Array Reshape(int m, int n) const;
    
    // Получить количество ссылок на данные
    operator int() const { return m_pDataRef->GetRefCount(); }
    
    // Дружественный оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Array& arr);
};

#endif