#include "list_string.h"


void String::deleteList() {
    MulticharacterBlock* prev;
    auto current = head;
    while (current != nullptr) {
        prev = current;
        current = current->next;
        delete[] prev->characters;
        delete prev;
    }
    blocks = 0;
    lastLength = 0;
}

void String::copyList(const String& string) {
    deleteList();
    if (string) {
        head = tail = new MulticharacterBlock(size);
        auto current = string.head;
        for (unsigned int i = 0; i < string.length(); ++i) {
            if (i % size == 0 && i != 0) {
                ++blocks;
                lastLength = 0;
                tail = tail->next = new MulticharacterBlock(size);
            }
            if (i % string.size == 0 && i != 0) {
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
            if (i % this->size == 0 and i != 0) {
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
    auto copyString = String(size);
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
            if (i % size == 0 && i != 0) {
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

long long String::find(const String &substring, unsigned int times) {
    if (!times) {
        times = 1;
    }
    if (substring) {
        unsigned int i, k, foundTimes = 0;
        MulticharacterBlock* current;
        auto sourceCurrent = head;
        auto substrCurrent = substring.head;
        for (unsigned int n = 0; n < length() - substring.length() + 1; ++n) {
            if (n % size == 0 && n != 0) {
                sourceCurrent = sourceCurrent->next;
            }
            current = sourceCurrent;
            for (i = n, k = 0; k < substring.length(); ++i, ++k) {
                if (i % size == 0 && i != n) {
                    current = current->next;
                }
                if (k % substring.size == 0 && k != 0) {
                    substrCurrent = substrCurrent->next;
                }
                if (current->characters[i % size] != substrCurrent->characters[k % substring.size]) {
                    break;
                }
            }
            if (k == substring.length() && ++foundTimes == times) {
                return n;
            }
        }
    }
    return NOT_FOUND;
}

void String::replace(const String &toReplace, const String &withReplace) {
    auto string = String();
    unsigned int n = 0;
    unsigned int k = 1;
    long long position = find(toReplace, k++);
    while (position != NOT_FOUND) {
        string += copy(n, position - n);
        string += withReplace;
        n = position + toReplace.length();
        position = find(toReplace, k++);
    }
    string += copy(n, length());
    copyList(string);
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
        if (i % text.size == 0 and i != 0) {
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
    auto string = String(a);
    string.concatenate(b);
    return string;
}

String operator+(const String &a, const char *b) {
    auto string = String(a);
    string.concatenate(b);
    return string;
}

String operator+(const String &a, const std::string &b) {
    auto string = String(a);
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

String::operator bool() const {
    return head != nullptr;
}
