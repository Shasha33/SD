#include <commands/CommandArguments.h>

CommandArguments::CommandArguments(const std::vector<Token> &argumentTokens)
        : argumentTokens(argumentTokens) {}

std::vector<Token> CommandArguments::asTokensVector() const {
    return argumentTokens;
}

size_t CommandArguments::countTokensWithType(const TokenType &tokenType) const {
    size_t count = 0;
    for (const auto &token : argumentTokens) {
        if (token.getTokenType() == tokenType) {
            count++;
        }
    }
    return count;
}

CommandArguments CommandArguments::strip() const {
    return this->lstrip().rstrip();
}

CommandArguments CommandArguments::lstrip() const {
    std::vector<Token> arguments = argumentTokens;
    size_t l = 0;
    while (l < arguments.size() && arguments[l].getTokenType() == TokenType::SPACE) {
        l++;
    }
    arguments.erase(arguments.begin(), arguments.begin() + l);
    return CommandArguments(arguments);
}

CommandArguments CommandArguments::rstrip() const {
    std::vector<Token> arguments = argumentTokens;

    bool isEndLast = !arguments.empty() && arguments.back().getTokenType() == TokenType::END;
    Token lastToken = Token(TokenType::END);
    if (isEndLast) {
        lastToken = arguments.back();
        arguments.pop_back();
    }

    size_t r = arguments.size();
    while (r > 0u && arguments[r - 1].getTokenType() == TokenType::SPACE) {
        r--;
    }
    arguments.erase(arguments.begin() + r, arguments.end());

    if (isEndLast) {
        arguments.push_back(lastToken);
    }

    return CommandArguments(arguments);
}

std::string CommandArguments::asString() const {
    std::string argumentsString;
    for (const auto &argument : argumentTokens) {
        argumentsString += argument.asString();
    }
    return argumentsString;
}

size_t CommandArguments::size() const {
    return argumentTokens.size();
}
