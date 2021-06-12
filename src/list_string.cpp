#include "list_string.h"


void String::deleteList() {
    MulticharacterBlock* prev;
    auto current = head;
    while (current != nullptr) {
        prev = current;
        current = current->next;
        delete prev;
    }
    blocks = 0;
    lastLength = 0;
    head = tail = nullptr;
}

void String::copyList(const String& string) {
    deleteList();
    if (string) {
        ++blocks;
        head = tail = new MulticharacterBlock(size);
        auto current = string.head;
        for (unsigned int i = 0; i < string.length(); ++i) {
            if (i % size == 0 && i) {
                ++blocks;
                lastLength = 0;
                tail = tail->next = new MulticharacterBlock(size);
            }
            if (i % string.size == 0 && i) {
                current = current->next;
            }
            tail->characters[lastLength++] = current->characters[i % string.size];
        }
    }
}

void String::setFromCString(const char* text) {
    lastLength = 0;
    if (*text) {
        blocks = 1;
        auto current = tail = head = new MulticharacterBlock(this->size);
        for (unsigned int i = 0; text[i]; ++i) {
            if (i % this->size == 0 && i) {
                tail = current = current->next = new MulticharacterBlock(this->size);
                ++blocks;
                lastLength = 0;
            }
            current->characters[lastLength++] = text[i];
        }
    } else {
        blocks = 0;
        tail = head = nullptr;
    }
}

void String::setSize(unsigned int value) {
    size = value ? value : DEFAULT_SIZE;
}


String::String(unsigned int size) {
    setSize(size);
    blocks = 0;
    lastLength = 0;
    tail = head = nullptr;
}

String::String(const char *text, unsigned int size) {
    setSize(size);
    setFromCString(text);
}

String::String(const std::string &text, unsigned int size) {
    setSize(size);
    setFromCString(text.c_str());
}

String::String(const String& string) {
    size = string.size;
    deleteList();
    concatenate(string);
}

String::~String() {
    deleteList();
}


unsigned int String::length() const {
    return (blocks != 0 ? (blocks - 1) * size + lastLength : 0);

}

String String::copy(unsigned int n, unsigned int k) {
    String copyString(size);
    if (k > 0 && length() > n) {
        auto sourceCurrent = head;
        unsigned int block = 0;
        while (n >= (block + 1) * size) {  // находим блок, с которого нужно проводить копирование
            sourceCurrent = sourceCurrent->next;
            ++block;
        }
        auto copyCurrent = copyString.head = copyString.tail = new MulticharacterBlock(copyString.size);
        ++copyString.blocks;
        for (unsigned int i = n - block * size, j = 0; block * size + i < length() && j < k; ++i, ++j) {
            if (i % size == 0 && i) {
                sourceCurrent = sourceCurrent->next;
            }
            if (j % copyString.size == 0 && j != 0) {
                copyCurrent = copyCurrent->next = copyString.tail = new MulticharacterBlock(copyString.size);
                ++copyString.blocks;
                copyString.lastLength = 0;
            }
            copyCurrent->characters[copyString.lastLength++] = sourceCurrent->characters[i % size];
        }
    }
    return copyString;
}


long long String::find(const String &substring) const {
    if (substring) {
        unsigned int i, k;
        MulticharacterBlock* current;
        auto sourceCurrent = head;
        auto substrCurrent = substring.head;
        for (unsigned int n = 0; n <= (long long)length() - substring.length(); ++n) {
            if (n % size == 0 && n) {
                sourceCurrent = sourceCurrent->next;
            }
            current = sourceCurrent;
            substrCurrent = substring.head;
            for (i = n, k = 0; k < substring.length(); ++i, ++k) {
                if (i % size == 0 && i != n) {
                    current = current->next;
                }
                if (k % substring.size == 0 && k) {
                    substrCurrent = substrCurrent->next;
                }
                if (current->characters[i % size] != substrCurrent->characters[k % substring.size]) {
                    break;
                }
            }
            if (k == substring.length()) {
                return n;
            }
        }
    }
    return NOT_FOUND;
}

long long String::find(const char *substring) const {
    return find(String(substring));
}

long long String::find(const std::string &substring) const {
    return find(String(substring));
}


void String::concatenate(const String& text) {
    if (head == nullptr and text.head != nullptr) {
        ++blocks;
        head = tail = new MulticharacterBlock(size);
    }
    auto aCurrent = tail;
    auto bCurrent = text.head;
    for (unsigned int i = 0; i < text.length(); ++i) {
        if (lastLength == size) {
            ++blocks;
            lastLength = 0;
            tail = aCurrent = aCurrent->next = new MulticharacterBlock(size);
        }
        if (i % text.size == 0 and i) {
            bCurrent = bCurrent->next;
        }
        aCurrent->characters[lastLength++] = bCurrent->characters[i % text.size];
    }
}

void String::concatenate(const char* text) {
    concatenate(String(text));
}

void String::concatenate(const std::string& text) {
    concatenate(String(text));
}


char *String::toCString() const {
    char* cString = new char[length() + 1] {};
    auto current = head;
    for (unsigned int i = 0; i < length(); ++i) {
        if (i % size == 0 and i) {
            current = current->next;
        }
        cString[i] = current->characters[i % size];
    }
    return cString;
}


std::ostream &operator<<(std::ostream &out, const String &string) {
    auto current = string.head;
    unsigned char characters;
    while (current != nullptr) {
        characters = current != string.tail ? string.size : string.lastLength;
        for (unsigned int i = 0; i < characters; ++i) {
            out << current->characters[i];
        }
        current = current->next;
    }
    return out;
}

String operator+(const String &a, const String &b) {
    String string(a);
    string.concatenate(b);
    return string;
}

String operator+(const String &a, const char *b) {
    String string(a);
    string.concatenate(b);
    return string;
}

String operator+(const String &a, const std::string &b) {
    String string(a);
    string.concatenate(b);
    return string;
}

String operator+(const char *a, const String &b) {
    String string(a);
    string.concatenate(b);
    return string;
}

String operator+(const std::string &a, const String &b) {
    String string(a);
    string.concatenate(b);
    return string;
}

void operator+=(String &a, const String &b) {
    a.concatenate(b);
}

void operator+=(String &a, const char *b) {
    a.concatenate(b);
}

void operator+=(String &a, const std::string &b) {
    a.concatenate(b);
}

String &String::operator=(const String& string) {
    if (this != &string) {
        copyList(string);
    }
    return *this;
}

String &String::operator=(const char *string) {
    deleteList();
    setFromCString(string);
    return *this;
}

String &String::operator=(const std::string &string) {
    deleteList();
    setFromCString(string.c_str());
    return *this;
}

String::operator bool() const {
    return head != nullptr;
}


String replace(const String &string, const String &toReplace, const String &withReplace) {
    String replacedString;
    String helperString(string);
    long long position = helperString.find(toReplace);
    while (position != NOT_FOUND) {
        replacedString = replacedString + helperString.copy(0, position) + withReplace;
        helperString = helperString.copy(position + toReplace.length(), helperString.length());
        position = helperString.find(toReplace);
    }
    replacedString += helperString;
    return replacedString;
}
