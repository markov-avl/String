#ifndef STRING_MULTICHARACTER_BLOCK_H
#define STRING_MULTICHARACTER_BLOCK_H


struct MulticharacterBlock {
    MulticharacterBlock* next;
    char* characters;

    explicit MulticharacterBlock(unsigned int);
};


#endif
