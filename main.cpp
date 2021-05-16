#include <iostream>
#include "list_string.h"


int main() {
    auto text = toString("1234567890123456");
    std::cout << "<" << text << ">" << std::endl;
    std::cout << text.length() << std::endl;
    return 0;
}
