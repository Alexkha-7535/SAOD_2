#include "array.h"

// Конструктор
Array::Array(int m, int n, int* p) : m_rows(m), m_cols(n)
{
    if (m <= 0 || n <= 0)
        throw std::invalid_argument("Array dimensions must be positive");
    
    int size = m * n;
    m_pDataRef = new _data(size, p);
}

// Конструктор копирования (view — данные не копируются)
Array::Array(const Array& other)
    : m_rows(other.m_rows), m_cols(other.m_cols), m_pDataRef(other.m_pDataRef)
{
    m_pDataRef->AddRef();
}

// Деструктор
Array::~Array()
{
    m_pDataRef->Release();
}

// Оператор присваивания
Array& Array::operator=(const Array& other)
{
    if (this != &other)
    {
        m_pDataRef->Release();
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_pDataRef = other.m_pDataRef;
        m_pDataRef->AddRef();
    }
    return *this;
}

// Доступ к элементу (чтение и запись)
int& Array::Item(int i, int j)
{
    if (i < 0 || i >= m_rows || j < 0 || j >= m_cols)
        throw std::out_of_range("Index out of range");
    
    int index = i * m_cols + j;
    return m_pDataRef->GetData()[index];
}

// Доступ к элементу (только чтение)
int Array::Item(int i, int j) const
{
    if (i < 0 || i >= m_rows || j < 0 || j >= m_cols)
        throw std::out_of_range("Index out of range");
    
    int index = i * m_cols + j;
    return m_pDataRef->GetData()[index];
}

// Изменение формы (возвращает новый view)
Array Array::Reshape(int m, int n) const
{
    if (m * n != m_rows * m_cols)
        throw std::invalid_argument("Array & View size mismatch");
    
    Array result(m, n, nullptr);
    
    // Освобождаем данные, которые только что выделились (они не нужны)
    result.m_pDataRef->Release();
    
    // Используем данные исходного массива
    result.m_pDataRef = m_pDataRef;
    result.m_pDataRef->AddRef();
    
    return result;
}

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const Array& arr)
{
    for (int i = 0; i < arr.m_rows; i++)
    {
        os << "[";
        for (int j = 0; j < arr.m_cols; j++)
        {
            os << arr.Item(i, j);
            if (j < arr.m_cols - 1)
                os << ", ";
        }
        os << "]" << std::endl;
    }
    return os;
}