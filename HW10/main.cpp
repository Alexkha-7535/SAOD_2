// main.cpp - Тестирование COBS
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "COBS.h"

using namespace std;

// Функция чтения файла в память
vector<unsigned char> readFile(const string& filename) {
    ifstream file(filename, ios::binary | ios::ate);
    if (!file) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return {};
    }
    
    streamsize size = file.tellg();
    file.seekg(0, ios::beg);
    
    vector<unsigned char> buffer(size);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
        cerr << "Ошибка чтения файла" << endl;
        return {};
    }
    
    return buffer;
}

// Функция записи файла из памяти
bool writeFile(const string& filename, const vector<unsigned char>& data) {
    ofstream file(filename, ios::binary);
    if (!file) {
        cerr << "Ошибка создания файла: " << filename << endl;
        return false;
    }
    
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
    return true;
}

// Вывод данных в шестнадцатеричном формате
void printHex(const unsigned char* data, unsigned len, unsigned maxBytes = 32) {
    unsigned toPrint = min(len, maxBytes);
    for (unsigned i = 0; i < toPrint; i++) {
        cout << hex << setw(2) << setfill('0') << (int)data[i] << " ";
        if ((i + 1) % 16 == 0) cout << endl;
    }
    if (len > maxBytes) {
        cout << "... (еще " << (len - maxBytes) << " байт)" << endl;
    }
    cout << dec << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    cout << "=== Алгоритм COBS ===" << endl;
    cout << "Выберите режим (e - кодирование, d - декодирование): ";
    
    char mode;
    cin >> mode;
    
    if (mode != 'e' && mode != 'd') {
        cerr << "Неверный режим!" << endl;
        return 1;
    }
    
    string inputFile, outputFile;
    cout << "Введите имя входного файла: ";
    cin >> inputFile;
    cout << "Введите имя выходного файла: ";
    cin >> outputFile;
    
    // Чтение входного файла
    auto inputData = readFile(inputFile);
    if (inputData.empty()) {
        return 1;
    }
    
    cout << "\nРазмер входных данных: " << inputData.size() << " байт" << endl;
    
    if (mode == 'e') {
        // Кодирование
        vector<unsigned char> encodedData(inputData.size() + inputData.size() / 254 + 1);
        
        unsigned encodedLen = COBSEncode(inputData.data(), inputData.size(), 
                                         encodedData.data());
        
        cout << "Размер закодированных данных: " << encodedLen << " байт" << endl;
        cout << "Первые байты закодированных данных:" << endl;
        printHex(encodedData.data(), encodedLen);
        
        // Проверка отсутствия байта 0
        if (check(encodedData.data(), encodedLen, 0)) {
            cout << "Проверка пройдена: байт 0 отсутствует в закодированных данных" << endl;
        } else {
            cout << "Ошибка: байт 0 найден в закодированных данных!" << endl;
        }
        
        // Запись в файл
        encodedData.resize(encodedLen);
        if (writeFile(outputFile, encodedData)) {
            cout << "Данные сохранены в файл: " << outputFile << endl;
        }
        
    } else {
        // Декодирование
        vector<unsigned char> decodedData(inputData.size());
        
        unsigned decodedLen = COBSDecode(inputData.data(), inputData.size(), 
                                         decodedData.data());
        
        cout << "Размер декодированных данных: " << decodedLen << " байт" << endl;
        cout << "Первые байты декодированных данных:" << endl;
        printHex(decodedData.data(), decodedLen);
        
        // Запись в файл
        decodedData.resize(decodedLen);
        if (writeFile(outputFile, decodedData)) {
            cout << "✓ Данные сохранены в файл: " << outputFile << endl;
        }
    }
    
    // Тестирование на примере
    cout << "\n=== Тестирование ===" << endl;
    const char* testStr = "Hello\0World\0Test";
    unsigned testLen = 17;
    
    cout << "Исходные данные: ";
    printHex(reinterpret_cast<const unsigned char*>(testStr), testLen);
    
    vector<unsigned char> testEncoded(testLen + 10);
    unsigned encodedLen = COBSEncode(reinterpret_cast<const unsigned char*>(testStr), 
                                     testLen, testEncoded.data());
    
    cout << "Закодированные данные: ";
    printHex(testEncoded.data(), encodedLen);
    
    vector<unsigned char> testDecoded(testLen);
    unsigned decodedLen = COBSDecode(testEncoded.data(), encodedLen, testDecoded.data());
    
    cout << "Декодированные данные: ";
    printHex(testDecoded.data(), decodedLen);
    
    if (decodedLen == testLen && 
        memcmp(testStr, testDecoded.data(), testLen) == 0) {
        cout << "Тест пройден успешно!" << endl;
    } else {
        cout << "Тест не пройден!" << endl;
    }
    
    return 0;
}