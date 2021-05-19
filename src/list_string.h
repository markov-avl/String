#ifndef STRING_LIST_STRING_H
#define STRING_LIST_STRING_H

#include <iostream>
#include "multicharacter_block.h"


class String {
private:
    unsigned int size{};          // количество символов в блоке
    unsigned int blocks{};        // количество многосимвольных блоков
    unsigned int lastLength{};    // количество символов в последнем блоке
    MulticharacterBlock* head{};  // ссылка на первый многосимвольный блок
    MulticharacterBlock* tail{};  // ссылка на последний многосимвольный блок

    void deleteList();
    void setFromCString(const char*);
    void setSize(unsigned int);

public:
    static const unsigned int DEFAULT_SIZE = 16;

    // конструкторы, оператор копирования и деструктор
    explicit String(unsigned int = DEFAULT_SIZE);
    explicit String(const char*, unsigned int = DEFAULT_SIZE);
    explicit String(const std::string&, unsigned int = DEFAULT_SIZE);
    String(const String&);
    ~String();

    // стандартные методы
    [[nodiscard]] unsigned int length() const;

    // конкатенация
    void concatenate(const String&);
    void concatenate(const char*);
    void concatenate(const std::string&);

    // перегрузка стандартных операторов
    friend std::ostream &operator<<(std::ostream&, const String&);
    friend String operator+(const String&, const String&);
    friend String operator+(const String&, const char*);
    friend String operator+(const String&, const std::string&);
    friend void operator+=(String&, const String&);
    friend void operator+=(String&, const char*);
    friend void operator+=(String&, const std::string&);
};


#endif
