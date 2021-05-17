#include <iostream>
#include "list_string.h"


int main() {
    auto text1 = toString("fhseofhse_", 4);
    auto text2 = toString("rhfsieuhfseiuhfsehf", 12);
    std::cout << "<" << text1 + text2 << ">" << std::endl;
    std::cout << text1.length() << std::endl;
    return 0;
}
