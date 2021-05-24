// tests framework: https://github.com/google/googletest
#include <iostream>
#include "gtest/gtest.h"
#include "list_string.h"


// bugs found after testing: 2


TEST(Length, StringLength) {
    char* cstring;
    std::string stdstring;
    String replacedString;

    for (unsigned int i = 0; i < 50; ++i) {
        String string("Hello world!", i);
        EXPECT_EQ(string.length(), 12);
        string += " I'm a length test";
        EXPECT_EQ(string.length(), 30);
        string = "";
        EXPECT_EQ(string.length(), 0);

        string = String("Привет мир!", i + 5);
        EXPECT_EQ(string.length(), 20);
        string += " Я тест функции " + String("длины");
        EXPECT_EQ(string.length(), 58);
        string = "";
        EXPECT_EQ(string.length(), 0);

        for (unsigned int j = 0; j < 50; ++j) {
            string = stdstring = "Hello world!";
            string = string.copy(i, j);
            cstring = string.toCString();
            try {
                stdstring = stdstring.substr(i, j);
                EXPECT_STREQ(cstring, stdstring.c_str());
            } catch (std::out_of_range &e) {  // substr падает, когда i > size
                EXPECT_STREQ(cstring, "");
            }
            delete[] cstring;
        }

        string = "Hello world!";

        replacedString = replace(string, String("No"), String("Yes"));
        EXPECT_EQ(replacedString.length(), 12);
        std::cout << replacedString << std::endl;

        replacedString = replace(string, String("o"), String("a"));
        EXPECT_EQ(replacedString.length(), 12);
        std::cout << replacedString << std::endl;

        replacedString = replace(replacedString, String("a"), String("aa"));
        EXPECT_EQ(replacedString.length(), 14);
        std::cout << replacedString << std::endl;

        replacedString = replace(replacedString, String("aa"), String("o"));
        EXPECT_EQ(replacedString.length(), 12);
        std::cout << replacedString << std::endl;

        replacedString = replace(string, String("l"), String("1234"));
        EXPECT_EQ(replacedString.length(), 21);
        std::cout << replacedString << std::endl;

        replacedString = replace(replacedString, String("3"), String("000"));
        EXPECT_EQ(replacedString.length(), 27);
        std::cout << replacedString << std::endl;

        replacedString = replace(replacedString, String("00"), String("1"));
        EXPECT_EQ(replacedString.length(), 24);
        std::cout << replacedString << std::endl;
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}