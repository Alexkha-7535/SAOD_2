#include "XMLProcessor.h"
#include <fstream>
#include <iostream>

using namespace std;

string XMLProcessor::readFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return "";
    }
    
    string content((istreambuf_iterator<char>(file)),
                   istreambuf_iterator<char>());
    return content;
}

bool XMLProcessor::writeFile(const string& filename, const string& content) {
    ofstream file(filename);
    if (!file) {
        cerr << "Ошибка создания файла: " << filename << endl;
        return false;
    }
    
    file << content;
    return true;
}

/**
 * Исправление пустых тегов <article>
 * Удаляет теги <article>, которые содержат только пробелы или знаки препинания
 * Сохраняет знаки препинания
 */
string XMLProcessor::fixEmptyArticleTags(const string& xml) {
    // Регулярное выражение для поиска пустых article тегов
    // <article> с возможным содержимым (только пробелы и знаки препинания) </article>
    regex emptyArticleRegex(R"(<article>\s*([.,;:!?]*)\s*</article>)");
    
    // Заменяем на сохранённые знаки препинания (группа 1)
    string result = regex_replace(xml, emptyArticleRegex, "$1");
    
    return result;
}

/**
 * Удаление пробелов перед знаками препинания
 * Находит пробелы перед знаками препинания и удаляет их
 */
string XMLProcessor::fixSpacesBeforePunctuation(const string& xml) {
    // Регулярное выражение: пробел(ы) перед знаком препинания
    // (\w) - слово (сохраняем)
    // \s+  - один или более пробелов
    // ([.,;:!?]) - знак препинания (сохраняем)
    regex spaceBeforePunctRegex(R"((\w)\s+([.,;:!?]))");
    
    // Заменяем на слово + знак препинания (без пробелов)
    string result = regex_replace(xml, spaceBeforePunctRegex, "$1$2");
    
    return result;
}

/**
 * Базовая проверка XML
 * Проверяет баланс тегов (упрощённая проверка)
 */
bool XMLProcessor::validateXML(const string& xml) {
    // Ищем все открывающие и закрывающие теги
    regex openTagRegex(R"(<(\w+)[^>]*>)");
    regex closeTagRegex(R"(</(\w+)>)");
    
    vector<string> tagStack;
    
    // Простая проверка - считаем теги
    auto openBegin = sregex_iterator(xml.begin(), xml.end(), openTagRegex);
    auto openEnd = sregex_iterator();
    
    auto closeBegin = sregex_iterator(xml.begin(), xml.end(), closeTagRegex);
    auto closeEnd = sregex_iterator();
    
    size_t openCount = distance(openBegin, openEnd);
    size_t closeCount = distance(closeBegin, closeEnd);
    
    // Базовая проверка: количество открывающих и закрывающих тегов должно совпадать
    // (это очень упрощённая проверка)
    return openCount == closeCount;
}

/**
 * Поиск листовых тегов (тегов без вложенных тегов)
 */
vector<string> XMLProcessor::findLeafTags(const string& xml) {
    vector<string> leafTags;
    
    // Регулярное выражение для листовых тегов:
    // <tag>текст без тегов</tag>
    regex leafTagRegex(R"(<(\w+)[^>]*>([^<>]*)</\1>)");
    
    auto begin = sregex_iterator(xml.begin(), xml.end(), leafTagRegex);
    auto end = sregex_iterator();
    
    for (auto it = begin; it != end; ++it) {
        leafTags.push_back(it->str());
    }
    
    return leafTags;
}