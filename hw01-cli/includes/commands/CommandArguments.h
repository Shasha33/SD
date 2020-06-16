#ifndef HW01_CLI_COMMANDARGUMENTS_H
#define HW01_CLI_COMMANDARGUMENTS_H

#include <string>
#include <vector>
#include <tokenizers/Token.h>

// Entity for representing arguments for
// command including all space tokens and end token.
// Command should parse it on its own.
// Each argument is the token.
class CommandArguments {
public:
    CommandArguments() = default;

    explicit CommandArguments(const std::vector<Token> &argumentTokens);

    // Returns command arguments in form of vector of tokens
    std::vector<Token> asTokensVector() const;

    // Calculates the number of argument-tokens with given type
    size_t countTokensWithType(const TokenType &tokenType) const;

    // Removes SPACE argument-tokens from the beginning and from the end
    CommandArguments strip() const;

    // Removes SPACE argument-tokens from the beginning
    CommandArguments lstrip() const;

    // Removes SPACE argument-tokens from the end
    CommandArguments rstrip() const;

    // Concatenates all tokens' representations into one string and returns it
    std::string asString() const;

    size_t size() const;

private:
    std::vector<Token> argumentTokens;
};


#endif //HW01_CLI_COMMANDARGUMENTS_H
