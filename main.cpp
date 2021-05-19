#include <iostream>
#include "list_string.h"


int main() {
    std::string text0 = "efesfsef:";
    auto text1 = String(4);
    auto text2 = String("rhfsieuhfseiuhfsehf");
    text1 += text1 + text2;
    std::cout << "<" << text1 << ">" << std::endl;
    std::cout << text1.length() << std::endl;
    return 0;
}
