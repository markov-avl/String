#include <iostream>
#include "list_string.h"


int main() {
    auto text1 = String("1234567890", 4);
    auto text2 = text1.copy(4, 9);
    std::cout << "<" << text2 << ">" << std::endl;
    std::cout << text2.length() << std::endl;
    return 0;
}
