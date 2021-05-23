#include "multicharacter_block.h"


MulticharacterBlock::MulticharacterBlock(unsigned int size) {
    next = nullptr;
    characters = new char[size];
}

MulticharacterBlock::~MulticharacterBlock() {
    delete[] characters;
}
