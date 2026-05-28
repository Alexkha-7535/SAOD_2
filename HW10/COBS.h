
#ifndef COBS_H
#define COBS_H

#include <cstddef>

/**
 * Функция кодирования COBS
 * @param src - входные данные
 * @param len - длина входных данных
 * @param dst - буфер для закодированных данных
 * @param reserved - зарезервированный байт (по умолчанию 0)
 * @return длина закодированных данных
 */
unsigned COBSEncode(const unsigned char* src, unsigned len, 
                    unsigned char* dst, unsigned char reserved = 0);

/**
 * Функция декодирования COBS
 * @param src - закодированные данные
 * @param len - длина закодированных данных
 * @param dst - буфер для декодированных данных
 * @param reserved - зарезервированный байт (по умолчанию 0)
 * @return длина декодированных данных
 */
unsigned COBSDecode(const unsigned char* src, unsigned len, 
                    unsigned char* dst, unsigned char reserved = 0);

/**
 * Функция проверки отсутствия зарезервированного байта
 * @param data - данные для проверки
 * @param len - длина данных
 * @param reserved - зарезервированный байт
 * @return true если байт не найден, false иначе
 */
bool check(const unsigned char* data, unsigned len, unsigned char reserved);

#endif // COBS_H