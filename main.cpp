#include <iostream>
#include "list_string.h"


int main() {
    auto text1 = String("abraka dabra abraka dabra abraka dabra   ", 17);
    auto toReplace = String("abra", 6);
    auto withReplace = String("bbbbbbbbbbbbbbbbbbbbbbb", 1);
    text1 = replace(text1, text1, withReplace);
    std::cout << text1 << std::endl;
    /*auto text2 = replace(text1, String("a"), String("aa"));
    std::cout << text1 << std::endl;
    auto text3 = replace(text2, String("a"), String("o"));
    std::cout << text3 << std::endl;*/
    return 0;
}