#include <iostream>
#include "list_string.h"


int main() {
    auto text = toString("12345678901234567");
    std::cout << "<" << text << ">" << std::endl;
    std::cout << text.length() << std::endl;
    return 0;
}
