#include "COBS.h"
#include <cstring>

unsigned COBSEncode(const unsigned char* src, unsigned len, 
                    unsigned char* dst, unsigned char reserved) {
    if (len == 0) return 0;
    
    unsigned read_index = 0;
    unsigned write_index = 1;
    unsigned code_index = 0;
    unsigned char code = 1;
    
    // Добавляем завершающий байт логически
    while (read_index < len) {
        if (src[read_index] == reserved) {
            // Нашли зарезервированный байт
            dst[code_index] = code;
            code = 1;
            code_index = write_index++;
            read_index++;
        } else {
            dst[write_index++] = src[read_index++];
            code++;
            
            // Если достигли максимального размера блока (254)
            if (code == 0xFF) {
                dst[code_index] = code;
                code = 1;
                code_index = write_index++;
            }
        }
    }
    
    // Обрабатываем последний блок
    dst[code_index] = code;
    
    // Добавляем завершающий байт (0)
    dst[write_index] = 0;
    
    return write_index + 1;
}

unsigned COBSDecode(const unsigned char* src, unsigned len, 
                    unsigned char* dst, unsigned char reserved) {
    if (len == 0) return 0;
    
    unsigned read_index = 0;
    unsigned write_index = 0;
    unsigned char code;
    
    while (read_index < len) {
        code = src[read_index];
        
        if (code == 0) break; // Конец данных
        
        read_index++;
        
        // Копируем блок данных
        for (unsigned char i = 1; i < code; i++) {
            if (read_index < len) {
                dst[write_index++] = src[read_index++];
            }
        }
        
        // Добавляем зарезервированный байт (если это не последний блок и не конец)
        if (code < 0xFF && read_index < len && src[read_index] != 0) {
            dst[write_index++] = reserved;
        }
    }
    
    return write_index;
}

bool check(const unsigned char* data, unsigned len, unsigned char reserved) {
    for (unsigned i = 0; i < len; i++) {
        if (data[i] == reserved) {
            return false;
        }
    }
    return true;
}