// tests framework: https://github.com/google/googletest
#include <iostream>
#include "gtest/gtest.h"
#include "list_string.h"


// bugs found after testing: 5


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

        replacedString = replace(string, String("o"), String("a"));
        EXPECT_EQ(replacedString.length(), 12);

        replacedString = replace(replacedString, String("a"), String("aa"));
        EXPECT_EQ(replacedString.length(), 14);

        replacedString = replace(replacedString, String("aa"), String("o"));
        EXPECT_EQ(replacedString.length(), 12);

        replacedString = replace(string, String("l"), String("1234"));
        EXPECT_EQ(replacedString.length(), 21);

        replacedString = replace(replacedString, String("3"), String("000"));
        EXPECT_EQ(replacedString.length(), 27);

        replacedString = replace(replacedString, String("00"), String("1"));
        EXPECT_EQ(replacedString.length(), 24);
    }
}

TEST(Replace, StringReplace) {
    auto text = String("abraka dabra");
    String text1, text2;

    text1 = replace(text, String(" "), String("_"));
    testing::internal::CaptureStdout();
    std::cout << text1;
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "abraka_dabra");

    text2 = replace(text1, String("a"), String("aa"));
    testing::internal::CaptureStdout();
    std::cout << text2;
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "aabraakaa_daabraa");

    text1 = replace(text2, String("a"), String("o"));
    testing::internal::CaptureStdout();
    std::cout << text1;
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "oobrookoo_doobroo");

    text2 = replace(text1, String("o"), String("aaaaa"));
    testing::internal::CaptureStdout();
    std::cout << text2;
    EXPECT_EQ(testing::internal::GetCapturedStdout(),
              "aaaaaaaaaabraaaaaaaaaakaaaaaaaaaa_daaaaaaaaaabraaaaaaaaaa");

    text2 = replace(text1, String("oo"), String("aaaaa"));
    testing::internal::CaptureStdout();
    std::cout << text2;
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "aaaaabraaaaakaaaaa_daaaaabraaaaa");

    String text3("abraka dabra abraka dabra abraka dabra ", 8);

    text1 = replace(text3, String("ra ab", 8), String("aa"));
    testing::internal::CaptureStdout();
    std::cout << text1;
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "abraka dabaaraka dabaaraka dabra ");

    text1 = replace(text1, String("ab", 3), String("ssss", 2));
    testing::internal::CaptureStdout();
    std::cout << text1;
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "ssssraka dssssaaraka dssssaaraka dssssra ");

    text1 = String("");
    text1 = replace(text1, String("", 3), String("", 2));
    testing::internal::CaptureStdout();
    std::cout << text1;
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "");

    text1 = String("hello");
    text1 = replace(text1, String("hello", 1), String("hello", 2));
    testing::internal::CaptureStdout();
    std::cout << text1;
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "hello");

    text1 = String("aaaabbaaaabbaaaabbaaaabbaaaabbaaaabbaaaabbaaaabbaaaabbaaaabbaaaabb");
    text1 = replace(text1, String("aaaa", 9), String("b", 1));
    testing::internal::CaptureStdout();
    std::cout << text1;
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");

    text1 = replace(text1, String("b", 9), String("aaaa_aaaa", 1));
    testing::internal::CaptureStdout();
    std::cout << text1;
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "aaaa_aaaaaaaa_aaaaaaaa_aaaaaaaa_aaaaaaaa_aaaaaaaa_aaaa"
                                                      "aaaa_aaaaaaaa_aaaaaaaa_aaaaaaaa_aaaaaaaa_aaaaaaaa_aaaa"
                                                      "aaaa_aaaaaaaa_aaaaaaaa_aaaaaaaa_aaaaaaaa_aaaaaaaa_aaaa"
                                                      "aaaa_aaaaaaaa_aaaaaaaa_aaaaaaaa_aaaaaaaa_aaaaaaaa_aaaa"
                                                      "aaaa_aaaaaaaa_aaaaaaaa_aaaaaaaa_aaaaaaaa_aaaaaaaa_aaaa"
                                                      "aaaa_aaaaaaaa_aaaaaaaa_aaaa");

    text1 = String("abraka dabra abraka dabra abraka dabra ", 7);
    text1 = replace(text1, String("ra ab", 2), String("aa", 1));
    testing::internal::CaptureStdout();
    std::cout << text1;
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "abraka dabaaraka dabaaraka dabra ");

    text1 = String("abraka dabraabraka dabraabraka dabra ", 7);
    text1 = replace(text1, String("raab", 2), String("aa", 1));
    testing::internal::CaptureStdout();
    std::cout << text1;
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "abraka dabaaraka dabaaraka dabra ");
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}