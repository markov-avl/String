#include "list_string.h"


String toString(const char* text) {
    auto string = String();
    if (text) {
        string.blocks = 1;
        string.last_length = 0;
        auto current = string.tail = string.head = new MulticharacterBlock;
        for (unsigned int i = 0; text[i]; ++i) {
            if (i % CHARACTERS == 0 and i != 0) {
                string.tail = current = current->next = new MulticharacterBlock;
                ++string.blocks;
                string.last_length = 0;
            }
            current->characters[i % CHARACTERS] = text[i];
            ++string.last_length;
        }
    }
    return string;
}

String toString(const std::string* text) {
    return toString(text->c_str());
}


String::String() {
    blocks = 0;
    last_length = 0;
    tail = head = nullptr;
}

String::~String() {
    MulticharacterBlock* prev;
    auto current = head;
    while (current != nullptr) {
        prev = current;
        current = current->next;
        delete prev;
    }
}


unsigned int String::length() const {
    return (blocks != 0 ? (blocks - 1) * CHARACTERS + last_length : 0);
}


void String::concatenate(const String& text) {
    // TODO
}

void String::concatenate(const char* text) {
    auto string = toString(text);
    concatenate(string);
}

void String::concatenate(const std::string* text) {
    auto string = toString(text);
    concatenate(string);
}


std::ostream &operator<<(std::ostream &out, const String &string) {
    auto current = string.head;
    unsigned char characters;
    while (current != nullptr) {
        characters = current != string.tail ? CHARACTERS : string.last_length;
        for (unsigned int i = 0; i < characters; ++i) {
            out << current->characters[i];
        }
        current = current->next;
    }
    out << '\0';
    return out;
}
