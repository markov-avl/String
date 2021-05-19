# Реализация строки String

## Вариант
**Односвязный список** из многосимвольных блоков с **фиксированной длиной**.

## Поля класса
1. **unsigned int** size - количество символов в блоке;
2. **unsigned int** blocks - количество многосимвольных блоков;
3. **unsigned int** lastLength - количество символов в последнем блоке;
4. **MulticharacterBlock*** head - ссылка на первый многосимвольный блок;
5. **MulticharacterBlock*** tail - ссылка на последний многосимвольный блок;
6. **unsigned int** DEFAULT_SIZE = 16 - длина многосимвольного блока по умолчанию (константа).

## Конструкторы, оператор копирования и деструктор
1. String(unsigned int = DEFAULT_SIZE) - главный конструктор;
2. String(const char*, unsigned int = DEFAULT_SIZE) - конструктор из CString;
3. String(const std::string&, unsigned int = DEFAULT_SIZE) - конструктор из STDString;
4. String(const String&) - оператор копирования;
5. ~String() - деструктор.

## Реализованные функции
1. **unsigned int** length() const - получение длины строки (каждый символ считается единицей измерения длины);
2. **void** concatenate(const String& | const char* | const std::string&) - сцепление строк;
3. **String** copy(unsigned int n, unsigned int k) - копирование k символов, начиная с n символа включительно;
4. **long long** find(const String&, unsigned int times) - поиск начала подстроки в строке, найденного times раз;
5. **void** replace(const String& toReplace, const String& withReplace) - замена всех подстрок toReplace на withReplace.

## Перегруженные операторы
1. **void** operator=(const String& | const char* | const std::string&) - присваивание;
2. **String** operator+(const String& a, const String& | const char* | const std::string& b) - сцепление a и b строк;
3. **void** operator+=(const String& a, const String& | const char* | const std::string& b) - сцепление a и b строк в a;
4. **std::ostream** &operator<<(std::ostream&, const String&) - вывод строки;
5. operator bool() const - возвращает истину, если строка не пуста, иначе - ложь.