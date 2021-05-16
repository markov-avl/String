#ifndef STRING_MULTICHARACTER_BLOCK_H
#define STRING_MULTICHARACTER_BLOCK_H


constexpr int CHARACTERS = 16;


struct MulticharacterBlock {
    MulticharacterBlock* next = nullptr;
    char characters[CHARACTERS] = {};
};


#endif
