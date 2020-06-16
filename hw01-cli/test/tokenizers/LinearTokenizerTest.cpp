#include <boost/test/unit_test.hpp>
#include <tokenizers/LinearTokenizer.h>

#include <iostream>

BOOST_AUTO_TEST_SUITE(LinearTokenizerSuite)

    BOOST_AUTO_TEST_CASE(testClear) {
        LinearTokenizer tokenizer;

        tokenizer.append("rekljngaergrkjg erljgejljgergrgjk 123");
        BOOST_CHECK_NE(TokenType::END, tokenizer.nextToken().getTokenType());

        tokenizer.clear();
        BOOST_CHECK_EQUAL(true, tokenizer.hasNextToken());
        BOOST_CHECK_EQUAL(TokenType::END, tokenizer.nextToken().getTokenType());
        BOOST_CHECK_EQUAL(false, tokenizer.hasNextToken());
    }

    BOOST_AUTO_TEST_CASE(testAppend) {
        LinearTokenizer tokenizer;
        Token token(TokenType::END);

        tokenizer = LinearTokenizer();
        tokenizer.append("x");
        BOOST_CHECK_EQUAL(true, tokenizer.hasNextToken());
        token = tokenizer.nextToken();
        BOOST_CHECK_EQUAL(TokenType::LITERAL, token.getTokenType());
        BOOST_CHECK_EQUAL("x", token.asString());

        tokenizer = LinearTokenizer();
        tokenizer.append("$");
        BOOST_CHECK_EQUAL(true, tokenizer.hasNextToken());
        token = tokenizer.nextToken();
        BOOST_CHECK_EQUAL(TokenType::DOLLAR, token.getTokenType());
        BOOST_CHECK_EQUAL("$", token.asString());

        tokenizer = LinearTokenizer();
        tokenizer.append("=");
        BOOST_CHECK_EQUAL(true, tokenizer.hasNextToken());
        token = tokenizer.nextToken();
        BOOST_CHECK_EQUAL(TokenType::ASSIGN, token.getTokenType());
        BOOST_CHECK_EQUAL("=", token.asString());

        tokenizer = LinearTokenizer();
        tokenizer.append("\t");
        BOOST_CHECK_EQUAL(true, tokenizer.hasNextToken());
        token = tokenizer.nextToken();
        BOOST_CHECK_EQUAL(TokenType::SPACE, token.getTokenType());
        BOOST_CHECK_EQUAL(" ", token.asString());

        tokenizer = LinearTokenizer();
        tokenizer.append(" ");
        BOOST_CHECK_EQUAL(true, tokenizer.hasNextToken());
        token = tokenizer.nextToken();
        BOOST_CHECK_EQUAL(TokenType::SPACE, token.getTokenType());
        BOOST_CHECK_EQUAL(" ", token.asString());
    }

    BOOST_AUTO_TEST_CASE(testHasNextTokenEmptyCommand) {
        LinearTokenizer tokenizer;
        Token token(TokenType::END);

        tokenizer.append("");
        tokenizer.append("");
        tokenizer.append("");

        BOOST_CHECK_EQUAL(true, tokenizer.hasNextToken());
        tokenizer.nextToken();
        BOOST_CHECK_EQUAL(false, tokenizer.hasNextToken());
    }

    BOOST_AUTO_TEST_CASE(testHasNextToken) {
        LinearTokenizer tokenizer;
        Token token(TokenType::END);

        tokenizer.append("a b \"c = d\"$x=56b");

        for (int i = 0; i < 10; i++) {
            BOOST_CHECK_EQUAL(true, tokenizer.hasNextToken());
            tokenizer.nextToken();
        }

        BOOST_CHECK_EQUAL(false, tokenizer.hasNextToken());
    }

    BOOST_AUTO_TEST_CASE(testNextToken) {
        LinearTokenizer tokenizer;
        Token token(TokenType::END);

        tokenizer.append("123 456 \"$x\"");
        tokenizer.append(" 4=b $x");

        BOOST_CHECK_EQUAL(true, tokenizer.hasNextToken());
        token = tokenizer.nextToken();
        BOOST_CHECK_EQUAL(TokenType::LITERAL, token.getTokenType());
        BOOST_CHECK_EQUAL("123", token.asString());

        BOOST_CHECK_EQUAL(true, tokenizer.hasNextToken());
        token = tokenizer.nextToken();
        BOOST_CHECK_EQUAL(TokenType::SPACE, token.getTokenType());
        BOOST_CHECK_EQUAL(" ", token.asString());

        BOOST_CHECK_EQUAL(true, tokenizer.hasNextToken());
        token = tokenizer.nextToken();
        BOOST_CHECK_EQUAL(TokenType::LITERAL, token.getTokenType());
        BOOST_CHECK_EQUAL("456", token.asString());

        BOOST_CHECK_EQUAL(true, tokenizer.hasNextToken());
        token = tokenizer.nextToken();
        BOOST_CHECK_EQUAL(TokenType::SPACE, token.getTokenType());
        BOOST_CHECK_EQUAL(" ", token.asString());

        BOOST_CHECK_EQUAL(true, tokenizer.hasNextToken());
        token = tokenizer.nextToken();
        BOOST_CHECK_EQUAL(TokenType::LITERAL, token.getTokenType());
        BOOST_CHECK_EQUAL("\"$x\"", token.asString());

        BOOST_CHECK_EQUAL(true, tokenizer.hasNextToken());
        token = tokenizer.nextToken();
        BOOST_CHECK_EQUAL(TokenType::SPACE, token.getTokenType());
        BOOST_CHECK_EQUAL(" ", token.asString());

        BOOST_CHECK_EQUAL(true, tokenizer.hasNextToken());
        token = tokenizer.nextToken();
        BOOST_CHECK_EQUAL(TokenType::LITERAL, token.getTokenType());
        BOOST_CHECK_EQUAL("4", token.asString());

        BOOST_CHECK_EQUAL(true, tokenizer.hasNextToken());
        token = tokenizer.nextToken();
        BOOST_CHECK_EQUAL(TokenType::ASSIGN, token.getTokenType());
        BOOST_CHECK_EQUAL("=", token.asString());

        BOOST_CHECK_EQUAL(true, tokenizer.hasNextToken());
        token = tokenizer.nextToken();
        BOOST_CHECK_EQUAL(TokenType::LITERAL, token.getTokenType());
        BOOST_CHECK_EQUAL("b", token.asString());

        BOOST_CHECK_EQUAL(true, tokenizer.hasNextToken());
        token = tokenizer.nextToken();
        BOOST_CHECK_EQUAL(TokenType::SPACE, token.getTokenType());
        BOOST_CHECK_EQUAL(" ", token.asString());

        BOOST_CHECK_EQUAL(true, tokenizer.hasNextToken());
        token = tokenizer.nextToken();
        BOOST_CHECK_EQUAL(TokenType::DOLLAR, token.getTokenType());
        BOOST_CHECK_EQUAL("$", token.asString());

        BOOST_CHECK_EQUAL(true, tokenizer.hasNextToken());
        token = tokenizer.nextToken();
        BOOST_CHECK_EQUAL(TokenType::LITERAL, token.getTokenType());
        BOOST_CHECK_EQUAL("x", token.asString());

        BOOST_CHECK_EQUAL(true, tokenizer.hasNextToken());
        token = tokenizer.nextToken();
        BOOST_CHECK_EQUAL(TokenType::END, token.getTokenType());

        BOOST_CHECK_EQUAL(false, tokenizer.hasNextToken());
    }

    BOOST_AUTO_TEST_CASE(testNextTokenEmptyCommand) {
        LinearTokenizer tokenizer;

        tokenizer.append("");
        tokenizer.append("");
        tokenizer.append("");

        BOOST_CHECK_EQUAL(true, tokenizer.hasNextToken());
        Token token = tokenizer.nextToken();
        BOOST_CHECK_EQUAL(TokenType::END, token.getTokenType());

        BOOST_CHECK_EQUAL(false, tokenizer.hasNextToken());
    }

BOOST_AUTO_TEST_SUITE_END()
