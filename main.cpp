#include <iostream>
#include "list_string.h"


int main() {
    auto text1 = String("101010", 15);
    auto text2 = String("0", 12);
    // std::cout << "<" << text1 << ">" << std::endl;
    std::cout << text1.find(text2, 2) << std::endl;
    return 0;
}