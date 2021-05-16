#ifndef STRING_LIST_STRING_H
#define STRING_LIST_STRING_H

#include <iostream>
#include "multicharacter_block.h"  // + добавляет константу CHARACTERS


class String {
private:
    unsigned int blocks;        // количество многосимвольных блоков
    unsigned int last_length;   // количество символов в последнем блоке
    MulticharacterBlock* head;  // ссылка на первый многосимвольный блок
    MulticharacterBlock* tail;  // ссылка на последний многосимвольный блок

public:
    // конструктор, деструктор и оператор копирования
    explicit String();
    ~String();
    String(String& string);

    // преобразование
    friend String toString(const char*);
    friend String toString(const std::string&);

    // стандартные методы
    [[nodiscard]] unsigned int length() const;

    // конкатенация
    void concatenate(const String&);
    void concatenate(const char*);
    void concatenate(const std::string&);

    // перегрузка стандартных операторов
    friend std::ostream &operator<<(std::ostream&, const String&);
    friend String operator+(const String& a, const String& b);
    friend String operator+(const String& a, const char* b);
    friend String operator+(const String& a, const std::string& b);
    friend void operator+=(String& a, const String& b);
    friend void operator+=(String& a, const char* b);
    friend void operator+=(String& a, const std::string& b);
};

String toString(const char*);
String toString(const std::string&);
String operator+(const String& a, const String& b);
String operator+(const String& a, const char* b);
String operator+(const String& a, const std::string& b);
void operator+=(String& a, const String& b);
void operator+=(String& a, const char* b);
void operator+=(String& a, const std::string& b);


#endif
