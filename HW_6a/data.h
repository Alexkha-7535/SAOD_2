#ifndef DATA_H
#define DATA_H

class _data
{
private:
    int* m_pData;      // указатель на массив целых чисел
    int m_nSize;       // размер массива
    int m_nRefCount;   // счётчик ссылок

public:
    // Конструктор: выделяет память и копирует данные (если p != 0)
    _data(int sz, int* p = nullptr);
    
    // Деструктор: освобождает память
    ~_data();
    
    // Увеличить счётчик ссылок
    void AddRef();
    
    // Уменьшить счётчик ссылок; при достижении 0 удаляет объект
    void Release();
    
    // Получить указатель на данные (только для чтения)
    const int* GetData() const { return m_pData; }
    
    // Получить указатель на данные (для изменения)
    int* GetData() { return m_pData; }
    
    // Получить размер
    int GetSize() const { return m_nSize; }
    
    // Получить счётчик ссылок
    int GetRefCount() const { return m_nRefCount; }
    
    // Дружественный класс Array (имеет доступ к приватным полям)
    friend class Array;
};

#endif