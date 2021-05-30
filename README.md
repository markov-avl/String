# Реализация строки String

## Вариант
**Односвязный список** из многосимвольных блоков с **фиксированной длиной**.

## Поля класса
1. `unsigned int size` - количество символов в блоке;
2. `unsigned int blocks` - количество многосимвольных блоков;
3. `unsigned int lastLength` - количество символов в последнем блоке;
4. `MulticharacterBlock* head` - ссылка на первый многосимвольный блок;
5. `MulticharacterBlock* tail` - ссылка на последний многосимвольный блок;
6. `unsigned int DEFAULT_SIZE = 16` - длина многосимвольного блока по умолчанию (константа).

## Конструкторы, оператор копирования и деструктор
1. `String(unsigned int = DEFAULT_SIZE)` - главный конструктор;
2. `String(const char*, unsigned int` = DEFAULT_SIZE) - конструктор из CString;
3. `String(const std::string&, unsigned int = DEFAULT_SIZE)` - конструктор из STDString;
4. `String(const String&)` - оператор копирования;
5. `~String()` - деструктор.

## Cтандартные методы
1. `unsigned int length() const` - получение длины строки (каждый символ считается единицей измерения длины);
2. `String copy(unsigned int n, unsigned int k)` - копирование k символов, начиная с n символа включительно;
3. Методы поиска - поиск начала подстроки в строке (первое вхождение слева):
    - `long long find(const String&) const`;
    - `long long find(const char*) const`;
    - `long long find(const std::string&) const`;
4. Методы конкатенация - сцепление строк:
    - `void concatenate(const String&)`;
    - `void concatenate(const char*)`;
    - `void concatenate(const std::string&)`.

## Перегрузка стандартных операторов
1. `friend std::ostream &operator<<(std::ostream&, const String&)` - вывод строки;
2. Оператор `+`:
    - `friend String operator+(const String&, const String&)`;
    - `friend String operator+(const String&, const char*)`;
    - `friend String operator+(const String&, const std::string&)`;
    - `friend String operator+(const char*, const String&)`;
    - `friend String operator+(const std::string&, const String&)`;
3. Оператор `+=`:
    - `friend void operator+=(String&, const String&)`;
    - `friend void operator+=(String&, const char*)`;
    - `friend void operator+=(String&, const std::string&)`;
4. Оператор присваивания:
    - `String& operator=(const String&)`;
    - `String& operator=(const char*)`;
    - `String& operator=(const std::string&)`.

## Бонусные методы:
1. `explicit operator bool() const` - возвращает истину, если строка не пуста, иначе - ложь.;
2. `char* toCString() const` - преобразование строки в массив char;
3. `String replace(const String &string, const String &toReplace, const String &withReplace)` - замена всех подстрок toReplace на withReplace в строке string;