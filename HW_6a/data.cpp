#include "data.h"
#include <cstring>

_data::_data(int sz, int* p) : m_nSize(sz), m_nRefCount(1)
{
    m_pData = new int[sz];
    
    if (p == nullptr)
    {
        // Зануляем данные
        for (int i = 0; i < sz; i++)
            m_pData[i] = 0;
    }
    else
    {
        // Копируем данные
        std::memcpy(m_pData, p, sz * sizeof(int));
    }
}

_data::~_data()
{
    delete[] m_pData;
}

void _data::AddRef()
{
    m_nRefCount++;
}

void _data::Release()
{
    m_nRefCount--;
    if (m_nRefCount == 0)
        delete this;
}