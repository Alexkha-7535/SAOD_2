#include <iostream>
#include <iomanip>
#include "XMLProcessor.h"

using namespace std;

int main() {
    // Настройка локали для поддержки русских символов (опционально)
    // setlocale(LC_ALL, "Russian");
    
    cout << "=== Обработка XML с регулярными выражениями ===" << endl << endl;
    
    // -------------------------------------------------------------------------
    // ШАГ 1: Чтение входного файла Dictionary.xml
    // -------------------------------------------------------------------------
    string xml = XMLProcessor::readFile("Dictionary.xml");
    
    // Если файл не найден — создаём тестовые данные для демонстрации
    if (xml.empty()) {
        cout << "⚠ Файл Dictionary.xml не найден. Используем тестовые данные..." << endl << endl;
        
        // Тестовый XML с обоими типами дефектов
        xml = R"(
<?xml version="1.0" encoding="UTF-8"?>
<dictionary>
    <!-- Раздел буквы А -->
    <letter><bold>А</bold></letter>
    
    <!-- Слово 1: корректное -->
    <main-word><bold>АБРИКОС</bold></main-word>
    <article>Косточковое плодовое дерево .</article>
    
    <!-- Слово 2: дефект 1 — пустой article -->
    <main-word><bold>АБСЦЕСС</bold></main-word>
    <article>   </article>
    
    <!-- Слово 3: дефект 1 — article только со знаком препинания -->
    <main-word><bold>АВАР</bold></main-word>
    <article>,</article>
    
    <!-- Слово 4: дефект 2 — пробелы перед знаками препинания -->
    <main-word><bold>АВАНГАРД</bold></main-word>
    <article>Передовой отряд . Передовая часть чего - либо !</article>
    
    <!-- Слово 5: оба дефекта сразу -->
    <main-word><bold>АВГУСТ</bold></main-word>
    <article>   Восьмой месяц года .   </article>
</dictionary>
)";
    }
    
    cout << "Исходные данные:" << endl;
    cout << "  Размер XML: " << xml.length() << " символов" << endl << endl;
    
    // -------------------------------------------------------------------------
    // ШАГ 2: АНАЛИЗ — поиск листовых тегов
    // -------------------------------------------------------------------------
    cout << "=== Анализ структуры: листовые теги ===" << endl;
    auto leafTags = XMLProcessor::findLeafTags(xml);
    
    cout << "Найдено листовых тегов: " << leafTags.size() << endl;
    cout << "Примеры (первые 5):" << endl;
    
    // Выводим не более 5 примеров, обрезая длинные
    for (size_t i = 0; i < min(leafTags.size(), size_t(5)); i++) {
        cout << "  " << (i+1) << ". ";
        string tag = leafTags[i];
        
        // Обрезаем для удобного вывода
        if (tag.length() > 60) {
            cout << tag.substr(0, 60) << "...";
        } else {
            cout << tag;
        }
        cout << endl;
    }
    cout << endl;
    
    // -------------------------------------------------------------------------
    // ШАГ 3: ИСПРАВЛЕНИЕ ДЕФЕКТА 1 — пустые теги <article>
    // -------------------------------------------------------------------------
    cout << "=== Исправление дефекта 1: пустые теги <article> ===" << endl;
    
    // Сохраняем копию до исправления для сравнения
    string beforeFix1 = xml;
    
    // Применяем исправление
    string fixed1 = XMLProcessor::fixEmptyArticleTags(xml);
    
    // Считаем, сколько исправлений было сделано
    // Используем тот же regex, что и в fixEmptyArticleTags
    regex emptyArticleCount(R"(<article>\s*[.,;:!?]*\s*</article>)");
    auto count1 = ptrdiff_t(distance(
        sregex_iterator(beforeFix1.begin(), beforeFix1.end(), emptyArticleCount),
        sregex_iterator()
    ));
    
    cout << "🔍 Найдено и исправлено пустых тегов <article>: " << count1 << endl;
    
    // Показываем пример исправления
    if (count1 > 0) {
        cout << "Пример:" << endl;
        cout << "  До: <article>   .   </article>" << endl;
        cout << "  После: ." << endl;
    }
    cout << endl;
    
    // -------------------------------------------------------------------------
    // ШАГ 4: ИСПРАВЛЕНИЕ ДЕФЕКТА 2 — пробелы перед знаками препинания
    // -------------------------------------------------------------------------
    cout << "=== Исправление дефекта 2: пробелы перед знаками препинания ===" << endl;
    
    string beforeFix2 = fixed1;  // Сохраняем состояние после первого исправления
    string fixed2 = XMLProcessor::fixSpacesBeforePunctuation(fixed1);
    
    // Считаем количество исправлений
    regex spaceBeforePunct(R"((\w)\s+([.,;:!?]))");
    auto count2 = ptrdiff_t(distance(
        sregex_iterator(beforeFix2.begin(), beforeFix2.end(), spaceBeforePunct),
        sregex_iterator()
    ));
    
    cout << "Найдено и исправлено пробелов перед знаками: " << count2 << endl;
    
    if (count2 > 0) {
        cout << "Пример:" << endl;
        cout << "  До: \"дерево .\"" << endl;
        cout << "  После: \"дерево.\"" << endl;
    }
    cout << endl;
    
    // -------------------------------------------------------------------------
    // ШАГ 5: ПРОВЕРКА РЕЗУЛЬТАТА
    // -------------------------------------------------------------------------
    cout << "=== Проверка корректности ===" << endl;
    
    // 5a. Проверка, что дефекты больше не находятся
    auto remainingEmpty = sregex_iterator(
        fixed2.begin(), fixed2.end(), emptyArticleCount);
    auto remainingSpaces = sregex_iterator(
        fixed2.begin(), fixed2.end(), spaceBeforePunct);
    
    if (remainingEmpty == sregex_iterator() && 
        remainingSpaces == sregex_iterator()) {
        cout << " Все целевые дефекты устранены" << endl;
    } else {
        cout << "Остались неисправленные дефекты:" << endl;
        if (remainingEmpty != sregex_iterator()) 
            cout << "   - пустые <article>: " 
                 << distance(remainingEmpty, sregex_iterator()) << endl;
        if (remainingSpaces != sregex_iterator())
            cout << "   - пробелы перед знаками: " 
                 << distance(remainingSpaces, sregex_iterator()) << endl;
    }
    
    // 5b. Базовая валидация структуры
    if (XMLProcessor::validateXML(fixed2)) {
        cout << " XML прошёл базовую проверку баланса тегов" << endl;
    } else {
        cout << " XML не прошёл проверку (возможно, это ложное срабатывание)" << endl;
    }
    cout << endl;
    
    // -------------------------------------------------------------------------
    // ШАГ 6: СОХРАНЕНИЕ РЕЗУЛЬТАТА
    // -------------------------------------------------------------------------
    string outputFile = "Dictionary_fixed.xml";
    if (XMLProcessor::writeFile(outputFile, fixed2)) {
        cout << " Исправленный XML сохранён в файл: " << outputFile << endl;
        cout << "  Размер: " << fixed2.length() << " символов" << endl;
    }
    cout << endl;
    
    // -------------------------------------------------------------------------
    // ШАГ 7: ОТВЕТЫ НА ТЕОРЕТИЧЕСКИЕ ВОПРОСЫ
    // -------------------------------------------------------------------------
    cout << "=== Ответы на вопросы по регулярным выражениям ===" << endl;
    
    cout << "1. Символ @ в C# (raw string literal):" << endl;
    cout << "   - Позволяет писать строки без экранирования обратных слешей" << endl;
    cout << "   - В C++ аналог: R\"(...)\" — raw string literal" << endl;
    cout << "   - Пример: @\"\\w+\" в C# = R\"(\\w+)\" в C++" << endl << endl;
    
    cout << "2. Шаблоны повторений:" << endl;
    cout << "   \\w*   — 0 или более словесных символов (может быть пусто)" << endl;
    cout << "   \\W*   — 0 или более НЕ словесных символов" << endl;
    cout << "   \\w+   — 1 или более словесных символов (обязательно хотя бы один)" << endl;
    cout << "   \\W+   — 1 или более НЕ словесных символов" << endl << endl;
    
    cout << "3. Шаблон [^<>]*:" << endl;
    cout << "   — 0 или более символов, КРОМЕ < и >" << endl;
    cout << "   — Используется для захвата текста внутри тегов без вложенных тегов" << endl << endl;
    
    cout << "4. Именованная группа:" << endl;
    cout << "   Синтаксис: (?<name>pattern) или (?'name'pattern)" << endl;
    cout << "   Пример: (?<word>\\w+) захватит слово в группу с именем 'word'" << endl;
    cout << "   Ссылка в замене: ${word} (в C++ std::regex: $1, $2... по номеру)" << endl << endl;
    
    cout << "5. Элементы в наших выражениях:" << endl;
    cout << "   a) Исчислители (*, +, ?): \\s*, \\w+, [.,;:!?]*" << endl;
    cout << "   b) Классы символов: [.,;:!?], [^<>], \\w, \\s" << endl;
    cout << "   c) Обычные символы: <, >, /, буквы в именах тегов" << endl;
    cout << "   d) Обратные ссылки: \\1 в </\\1> для проверки парности тегов" << endl;
    cout << "   e) Подстановки: $1, $2 в строке замены для вставки групп" << endl;
    
    cout << "\n=== Работа завершена ===" << endl;
    return 0;
}
