#ifndef HW01_CLI_TOKEN_H
#define HW01_CLI_TOKEN_H

#include <string>

enum TokenType {
    PIPE, SPACE, END, ASSIGN, LITERAL, DOLLAR
};

// The unit of tokenization process.
class Token {
public:
    explicit Token(const TokenType &tokenType, const std::string &tokenContent = "");

    TokenType getTokenType() const;

    // Creates the string representation of token.
    const std::string &asString() const;

    // Checks whether the string representation
    // is empty or not
    bool empty() const;

private:
    TokenType tokenType;
    std::string tokenContent;
};


#endif //HW01_CLI_TOKEN_H
