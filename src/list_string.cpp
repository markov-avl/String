#include "list_string.h"


String toString(const char* text, unsigned int size) {
    auto string = String(size);
    if (text) {
        string.blocks = 1;
        string.last_length = 0;
        auto current = string.tail = string.head = new MulticharacterBlock(size);
        for (unsigned int i = 0; text[i]; ++i) {
            if (i % size == 0 and i != 0) {
                string.tail = current = current->next = new MulticharacterBlock(size);
                ++string.blocks;
                string.last_length = 0;
            }
            current->characters[i % size] = text[i];
            ++string.last_length;
        }
    }
    return string;
}

String toString(const std::string& text, unsigned int size) {
    return toString(text.c_str(), size);
}


void String::deleteList() {
    MulticharacterBlock* prev;
    auto current = head;
    while (current != nullptr) {
        prev = current;
        current = current->next;
        delete[] prev->characters;
        delete prev;
    }
}


String::String(unsigned int size) {
    this->size = size;
    blocks = 0;
    last_length = 0;
    tail = head = nullptr;
}

String::String(const String& string) {
    size = string.size;
    blocks = 0;
    last_length = 0;
    if (head != nullptr) {
        deleteList();
    }
    concatenate(string);
}

String::~String() {
    deleteList();
}


unsigned int String::length() const {
    return (blocks != 0 ? (blocks - 1) * size + last_length : 0);  // TODO: починить
}


void String::concatenate(const String& text) {
    if (head == nullptr and text.head != nullptr) {
        head = tail = new MulticharacterBlock(size);
    }
    auto aCurrent = tail;
    auto bCurrent = text.head;
    for (unsigned int i = 0; i < text.length(); ++i) {
        if (last_length == size) {
            tail = aCurrent = aCurrent->next = new MulticharacterBlock(size);
            ++blocks;
            last_length = 0;
        }
        if (i % text.size == 0 and i != 0) {
            bCurrent = bCurrent->next;
        }
        aCurrent->characters[last_length++] = bCurrent->characters[i % text.size];
    }
}

void String::concatenate(const char* text) {
    auto string = toString(text);
    concatenate(string);
}

void String::concatenate(const std::string& text) {
    auto string = toString(text);
    concatenate(string);
}


std::ostream &operator<<(std::ostream &out, const String &string) {
    auto current = string.head;
    unsigned char characters;
    while (current != nullptr) {
        characters = current != string.tail ? string.size : string.last_length;
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
