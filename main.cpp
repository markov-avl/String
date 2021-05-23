#include <iostream>
#include "list_string.h"


int main() {
//    auto text1 = String("Borya nyuhaet beabru", 1);
////    auto toReplace = String(" ", 1);
////    auto withReplace = String("_", 1);
////    text1.replace(toReplace, withReplace);
//    text1.replace(String("a"), String("aa"));
//    std::cout << text1 << std::endl;
//    text1.replace(String("aa"), String("oooo"));
//    std::cout << text1 << std::endl;
//    text1.replace(String("ooo"), String("a"));
//    std::cout << text1 << std::endl;

//    auto text1 = String("Lesha nyuhaet beabru", 1 << 8);
//    std::cout << text1.length() << std::endl;
////    auto toReplace = String(" ", 1);
////    auto withReplace = String("_", 1);
////    text1.replace(toReplace, withReplace);
//    text1.replace(String("a"), String("aa"));
//    std::cout << text1 << std::endl;
//    text1.replace(String("aa"), String("oooo"));
//    std::cout << text1 << std::endl;
//    text1.replace(String("ooo"), String("a"));
//    std::cout << text1 << std::endl;

    auto text1 = String("aaaa", 1 << 8);
    std::cout << text1.length() << std::endl;
//    auto toReplace = String(" ", 1);
//    auto withReplace = String("_", 1);
//    text1.replace(toReplace, withReplace);
    text1.replace(String("a"), String("aa"));
    std::cout << text1 << std::endl;
    text1.replace(String("a"), String("oooo"));
    std::cout << text1 << std::endl;
    text1.replace(String("oooooooo"), String("a"));
    std::cout << text1 << std::endl;
    return 0;
}