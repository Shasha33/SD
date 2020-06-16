#include <boost/test/unit_test.hpp>
#include <tokenizers/Token.h>

#include <iostream>
#include <vector>
#include <string>

BOOST_AUTO_TEST_SUITE(TokenSuite)

    BOOST_AUTO_TEST_CASE(testEmpty) {
        Token token(TokenType::PIPE, "");
        BOOST_CHECK_EQUAL(true, token.empty());

        token = Token(TokenType::SPACE, "");
        BOOST_CHECK_EQUAL(true, token.empty());

        token = Token(TokenType::END, "");
        BOOST_CHECK_EQUAL(true, token.empty());

        token = Token(TokenType::ASSIGN, "");
        BOOST_CHECK_EQUAL(true, token.empty());

        token = Token(TokenType::LITERAL, "");
        BOOST_CHECK_EQUAL(true, token.empty());

        token = Token(TokenType::DOLLAR, "");
        BOOST_CHECK_EQUAL(true, token.empty());
    }

    BOOST_AUTO_TEST_CASE(testAsString) {
        std::vector<std::string> contents = {
                "",
                "aer gle aglg g aejgl aregrje",
                "12 21kjwkj awe;kj &?<123=2=>!@#$%^&*()_"
        };

        for (const std::string &content : contents) {
            Token token(TokenType::SPACE, content);
            BOOST_CHECK_EQUAL(content, token.asString());

            token = Token(TokenType::PIPE, content);
            BOOST_CHECK_EQUAL(content, token.asString());

            token = Token(TokenType::END, content);
            BOOST_CHECK_EQUAL(content, token.asString());

            token = Token(TokenType::ASSIGN, content);
            BOOST_CHECK_EQUAL(content, token.asString());

            token = Token(TokenType::LITERAL, content);
            BOOST_CHECK_EQUAL(content, token.asString());

            token = Token(TokenType::DOLLAR, content);
            BOOST_CHECK_EQUAL(content, token.asString());
        }
    }

    BOOST_AUTO_TEST_CASE(testGetTokenType) {
        std::vector<std::string> contents = {
                "",
                "aer gle aglg g aejgl aregrje",
                "12 21kjwkj awe;kj &?<123=2=>!@#$%^&*()_"
        };

        for (const std::string &content : contents) {
            Token token(TokenType::SPACE, content);
            BOOST_CHECK_EQUAL(TokenType::SPACE, token.getTokenType());

            token = Token(TokenType::PIPE, content);
            BOOST_CHECK_EQUAL(TokenType::PIPE, token.getTokenType());

            token = Token(TokenType::END, content);
            BOOST_CHECK_EQUAL(TokenType::END, token.getTokenType());

            token = Token(TokenType::ASSIGN, content);
            BOOST_CHECK_EQUAL(TokenType::ASSIGN, token.getTokenType());

            token = Token(TokenType::LITERAL, content);
            BOOST_CHECK_EQUAL(TokenType::LITERAL, token.getTokenType());

            token = Token(TokenType::DOLLAR, content);
            BOOST_CHECK_EQUAL(TokenType::DOLLAR, token.getTokenType());
        }
    }

BOOST_AUTO_TEST_SUITE_END()
