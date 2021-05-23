// tests framework: https://github.com/google/googletest
#include <iostream>
#include "gtest/gtest.h"
#include "list_string.h"


// bugs found after testing: 2


TEST(Length, StringLength) {
    String string;
    std::string stdstring;

    for (unsigned int i = 0; i < 50; ++i) {
        string = String("Hello world!", i);
        EXPECT_EQ(string.length(), 12);
        string += " I'm a length test";
        EXPECT_EQ(string.length(), 30);
        string = "";
        EXPECT_EQ(string.length(), 0);

        string = String("Привет мир!", i);
        EXPECT_EQ(string.length(), 20);
        string += " Я тест функции длины";
        EXPECT_EQ(string.length(), 58);
        string = "";
        EXPECT_EQ(string.length(), 0);

        for (unsigned int j = 1; j < 50; ++j) {
            string = stdstring = "Hello world!";
            string = string.copy(i, j);
            try {
                stdstring = stdstring.substr(i, j);
                EXPECT_EQ(string, stdstring); // нельзя так сравнивать
            } catch (int) {
                EXPECT_EQ(string, "");   // нельзя так сравнивать
            }
        }
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}