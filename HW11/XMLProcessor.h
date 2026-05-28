#ifndef XMLPROCESSOR_H
#define XMLPROCESSOR_H

#include <string>
#include <vector>
#include <regex>

class XMLProcessor {
public:
    // Чтение файла
    static std::string readFile(const std::string& filename);
    
    // Запись файла
    static bool writeFile(const std::string& filename, const std::string& content);
    
    // Дефект 1: Удаление пустых тегов article
    static std::string fixEmptyArticleTags(const std::string& xml);
    
    // Дефект 2: Удаление пробелов перед знаками препинания
    static std::string fixSpacesBeforePunctuation(const std::string& xml);
    
    // Проверка корректности XML (базовая)
    static bool validateXML(const std::string& xml);
    
    // Поиск листовых тегов
    static std::vector<std::string> findLeafTags(const std::string& xml);
};

#endif