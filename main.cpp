#include <iostream>
#include "list_string.h"


int main() {
    auto text1 = String("11010", 15);
    auto toReplace = String("1", 12);
    auto withReplace = String("абобА", 1);
    text1.replace(toReplace, withReplace);
    std::cout << text1 << std::endl;
    return 0;
}