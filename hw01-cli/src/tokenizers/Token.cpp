#include <tokenizers/Token.h>

TokenType Token::getTokenType() const {
    return tokenType;
}

Token::Token(const TokenType &tokenType, const std::string &tokenContent)
        : tokenType(tokenType), tokenContent(tokenContent) {}

const std::string &Token::asString() const {
    return tokenContent;
}

bool Token::empty() const {
    return tokenContent.empty();
}
