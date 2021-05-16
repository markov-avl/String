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
    // конструктор и деструктор
    explicit String();
    ~String();

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
};

String toString(const char*);
String toString(const std::string&);


#endif
