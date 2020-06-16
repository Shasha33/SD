#include <boost/test/unit_test.hpp>
#include <commands/CommandArguments.h>

#include <vector>

BOOST_AUTO_TEST_SUITE(CommandArgumentsSuite)

    BOOST_AUTO_TEST_CASE(testAsString) {
        std::vector<Token> tokens = {
                Token(TokenType::SPACE, " "),
                Token(TokenType::DOLLAR, "$"),
                Token(TokenType::LITERAL, "x"),
                Token(TokenType::SPACE, " "),
                Token(TokenType::LITERAL, "123"),
                Token(TokenType::END)
        };
        CommandArguments commandArguments(tokens);
        BOOST_CHECK_EQUAL(" $x 123", commandArguments.asString());
    }

    BOOST_AUTO_TEST_CASE(testAsStringEmptyString) {
        std::vector<Token> tokens = {
                Token(TokenType::END)
        };
        CommandArguments commandArguments(tokens);
        BOOST_CHECK_EQUAL("", commandArguments.asString());
    }

    BOOST_AUTO_TEST_CASE(testAsTokensVector) {
        std::vector<Token> expectedTokens;
        std::vector<TokenType> tokenTypes = {
                PIPE, SPACE, END, ASSIGN, LITERAL, DOLLAR
        };
        for (int i = 0; i < 100; i++) {
            TokenType type = tokenTypes[i % (int) tokenTypes.size()];
            std::string stringRepresentation = std::to_string(i);
            expectedTokens.emplace_back(type, stringRepresentation);
        }
        CommandArguments commandArguments(expectedTokens);
        std::vector<Token> foundTokens = commandArguments.asTokensVector();
        BOOST_CHECK_EQUAL(expectedTokens.size(), foundTokens.size());
        for (size_t i = 0; i < expectedTokens.size(); i++) {
            BOOST_CHECK_EQUAL(expectedTokens[i].getTokenType(), foundTokens[i].getTokenType());
            BOOST_CHECK_EQUAL(expectedTokens[i].asString(), foundTokens[i].asString());
        }
    }

    BOOST_AUTO_TEST_CASE(testCountTokensWithType) {
        std::vector<Token> expectedTokens;
        std::vector<TokenType> tokenTypes = {
                PIPE, SPACE, END, ASSIGN, LITERAL, DOLLAR
        };
        for (int i = 0; i < 100; i++) {
            TokenType type = tokenTypes[i % (int) tokenTypes.size()];
            std::string stringRepresentation = std::to_string(i);
            expectedTokens.emplace_back(type, stringRepresentation);
        }
        CommandArguments commandArguments(expectedTokens);
        for (const TokenType &type : tokenTypes) {
            size_t expectedCount = 0;
            for (const Token &token : expectedTokens) {
                if (token.getTokenType() == type) {
                    expectedCount++;
                }
            }
            BOOST_CHECK_EQUAL(expectedCount, commandArguments.countTokensWithType(type));
        }
    }

    BOOST_AUTO_TEST_CASE(testLstripe) {
        std::vector<Token> middleTokens = {
                Token(TokenType::LITERAL, "x"),
                Token(TokenType::SPACE, " "),
                Token(TokenType::LITERAL, "y")
        };
        for (size_t leftSpaces = 0u; leftSpaces < 3u; leftSpaces++) {
            for (size_t rightSpaces = 0u; rightSpaces < 3u; rightSpaces++) {
                std::vector<Token> tokens;
                for (size_t i = 0u; i < leftSpaces; i++) {
                    tokens.emplace_back(TokenType::SPACE, " ");
                }
                for (const Token &token : middleTokens) {
                    tokens.push_back(token);
                }
                for (size_t i = 0u; i < rightSpaces; i++) {
                    tokens.emplace_back(TokenType::SPACE, " ");
                }
                std::vector<Token> foundTokens = CommandArguments(tokens).lstrip().asTokensVector();
                BOOST_CHECK_EQUAL(3u + rightSpaces, foundTokens.size());

                BOOST_CHECK_EQUAL(TokenType::LITERAL, foundTokens[0u].getTokenType());
                BOOST_CHECK_EQUAL("x", foundTokens[0u].asString());

                BOOST_CHECK_EQUAL(TokenType::SPACE, foundTokens[1u].getTokenType());
                BOOST_CHECK_EQUAL(" ", foundTokens[1u].asString());

                BOOST_CHECK_EQUAL(TokenType::LITERAL, foundTokens[2u].getTokenType());
                BOOST_CHECK_EQUAL("y", foundTokens[2u].asString());

                for (size_t i = 3u; i < foundTokens.size(); i++) {
                    BOOST_CHECK_EQUAL(TokenType::SPACE, foundTokens[i].getTokenType());
                    BOOST_CHECK_EQUAL(" ", foundTokens[i].asString());
                }
            }
        }
    }

    BOOST_AUTO_TEST_CASE(testRstripe) {
        std::vector<Token> middleTokens = {
                Token(TokenType::LITERAL, "x"),
                Token(TokenType::SPACE, " "),
                Token(TokenType::LITERAL, "y")
        };
        for (size_t leftSpaces = 0u; leftSpaces < 3u; leftSpaces++) {
            for (size_t rightSpaces = 0u; rightSpaces < 3u; rightSpaces++) {
                std::vector<Token> tokens;
                for (size_t i = 0u; i < leftSpaces; i++) {
                    tokens.emplace_back(TokenType::SPACE, " ");
                }
                for (const Token &token : middleTokens) {
                    tokens.push_back(token);
                }
                for (size_t i = 0u; i < rightSpaces; i++) {
                    tokens.emplace_back(TokenType::SPACE, " ");
                }
                std::vector<Token> foundTokens = CommandArguments(tokens).rstrip().asTokensVector();
                BOOST_CHECK_EQUAL(3u + leftSpaces, foundTokens.size());

                for (size_t i = 0; i < leftSpaces; i++) {
                    BOOST_CHECK_EQUAL(TokenType::SPACE, foundTokens[i].getTokenType());
                    BOOST_CHECK_EQUAL(" ", foundTokens[i].asString());
                }

                BOOST_CHECK_EQUAL(TokenType::LITERAL, foundTokens[leftSpaces + 0u].getTokenType());
                BOOST_CHECK_EQUAL("x", foundTokens[leftSpaces + 0u].asString());

                BOOST_CHECK_EQUAL(TokenType::SPACE, foundTokens[leftSpaces + 1u].getTokenType());
                BOOST_CHECK_EQUAL(" ", foundTokens[leftSpaces + 1u].asString());

                BOOST_CHECK_EQUAL(TokenType::LITERAL, foundTokens[leftSpaces + 2u].getTokenType());
                BOOST_CHECK_EQUAL("y", foundTokens[leftSpaces + 2u].asString());
            }
        }
    }

    BOOST_AUTO_TEST_CASE(testStripe) {
        std::vector<Token> middleTokens = {
                Token(TokenType::LITERAL, "x"),
                Token(TokenType::SPACE, " "),
                Token(TokenType::LITERAL, "y")
        };
        for (size_t leftSpaces = 0u; leftSpaces < 3u; leftSpaces++) {
            for (size_t rightSpaces = 0u; rightSpaces < 3u; rightSpaces++) {
                std::vector<Token> tokens;
                for (size_t i = 0u; i < leftSpaces; i++) {
                    tokens.emplace_back(TokenType::SPACE, " ");
                }
                for (const Token &token : middleTokens) {
                    tokens.push_back(token);
                }
                for (size_t i = 0u; i < rightSpaces; i++) {
                    tokens.emplace_back(TokenType::SPACE, " ");
                }
                std::vector<Token> foundTokens = CommandArguments(tokens).strip().asTokensVector();
                BOOST_CHECK_EQUAL(3u, foundTokens.size());

                BOOST_CHECK_EQUAL(TokenType::LITERAL, foundTokens[0u].getTokenType());
                BOOST_CHECK_EQUAL("x", foundTokens[0u].asString());

                BOOST_CHECK_EQUAL(TokenType::SPACE, foundTokens[1u].getTokenType());
                BOOST_CHECK_EQUAL(" ", foundTokens[1u].asString());

                BOOST_CHECK_EQUAL(TokenType::LITERAL, foundTokens[2u].getTokenType());
                BOOST_CHECK_EQUAL("y", foundTokens[2u].asString());
            }
        }
    }

BOOST_AUTO_TEST_SUITE_END()
