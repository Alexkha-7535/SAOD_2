#include <iostream>
#include <iomanip>
#include "XMLProcessor.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    
    cout << "=== Обработка XML с регулярными выражениями ===" << endl;
    
    // Чтение файла Dictionary.xml
    string xml = XMLProcessor::readFile("Dictionary.xml");
    
    if (xml.empty()) {
        cout << "Не удалось прочитать файл Dictionary.xml" << endl;
        cout << "Создаём тестовые данные..." << endl;
        
        // Тестовые данные с дефектами
        xml = R"(
<?xml version="1.0" encoding="UTF-8"?>
<dictionary>
    <letter><bold>А</bold></letter>
    <main-word><bold>СЛОВО1</bold></main-word>
    <article>Трактовка слова 1 .</article>
    
    <main-word><bold>СЛОВО2</bold></main-word>
    <article>   </article>
    
    <main-word><bold>СЛОВО3</bold></main-word>
    <article>,</article>
    
    <main-word><bold>СЛОВО4</bold></main-word>
    <article>Трактовка слова 4 . Ещё текст !</article>
</dictionary>
)";
    }
    
    cout << "Исходный размер XML: " << xml.length() << " символов" << endl;
    
    // Поиск листовых тегов
    cout << "\n=== Листовые теги ===" << endl;
    auto leafTags = XMLProcessor::findLeafTags(xml);
    cout << "Найдено листовых тегов: " << leafTags.size() << endl;
    for (size_t i = 0; i < min(leafTags.size(), size_t(5)); i++) {
        cout << (i+1) << ". " << leafTags[i].substr(0, 60);
        if (leafTags[i].length() > 60) cout << "...";
        cout << endl;
    }
    
    // Исправление дефекта 1: пустые теги article
    cout << "\n=== Исправление дефекта 1: пустые теги ===" << endl;
    string fixed1 = XMLProcessor::fixEmptyArticleTags(xml);
    
    // Считаем сколько пустых тегов было удалено
    regex emptyArticleCount(R"(<article>\s*[.,;:!?]*\s*</article>)");
    auto count1 = ptrdiff_t(distance(
        sregex_iterator(xml.begin(), xml.end(), emptyArticleCount),
        sregex_iterator()
    ));
    
    cout << "Найдено и исправлено пустых тегов <article>: " << count1 << endl;
    
    // Исправление дефекта 2: пробелы перед знаками препинания
    cout << "\n=== Исправление дефекта 2: пробелы перед знаками препинания ===" << endl;
    string fixed2 = XMLProcessor::fixSpacesBeforePunctuation(fixed1);
    
    // Считаем сколько исправлений сделано
    regex spaceBeforePunct(R"((\w)\s+([.,;:!?]))");
    auto count2 = ptrdiff_t(distance(
        sregex_iterator(fixed1.begin(), fixed1.end(), spaceBeforePunct),
        sregex_iterator()
    ));
    
    cout << "Найдено и исправлено пробелов перед знаками препинания: " << count2 << endl;
    
    // Проверка XML
    cout << "\n=== Проверка XML ===" << endl;
    if (XMLProcessor::validateXML(fixed2)) {
        cout << " XML прошёл базовую проверку" << endl;
    } else {
        cout << " XML не прошёл проверку" << endl;
    }
    
    // Сохранение результата
    string outputFile = "Dictionary_fixed.xml";
    if (XMLProcessor::writeFile(outputFile, fixed2)) {
        cout << " Исправленный XML сохранён в файл: " << outputFile << endl;
    }
    
    // Вывод примеров исправлений
    cout << "\n=== Примеры исправлений ===" << endl;
    cout << "До: <article>   </article>" << endl;
    cout << "После: (удалено, сохранены только знаки препинания)" << endl;
    cout << endl;
    cout << "До: слово ." << endl;
    cout << "После: слово." << endl;
    
    // Ответы на теоретические вопросы
    cout << "\n=== Теоретические вопросы ===" << endl;
    cout << "1. Символ @ в C# означает литерал строки без обработки escape-последовательностей" << endl;
    cout << "   В C++ мы используем R\"(...)\" для raw string literals" << endl;
    cout << endl;
    cout << "2. Шаблоны:" << endl;
    cout << "   \\w*  - 0 или более словесных символов" << endl;
    cout << "   \\W*  - 0 или более НЕ словесных символов" << endl;
    cout << "   \\w+  - 1 или более словесных символов" << endl;
    cout << "   \\W+  - 1 или более НЕ словесных символов" << endl;
    cout << endl;
    cout << "3. [^<>]* - 0 или более символов, кроме < и >" << endl;
    cout << endl;
    cout << "4. Именованная группа: (?<name>pattern) или (?'name'pattern)" << endl;
    
    return 0;
}