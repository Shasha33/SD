#ifndef HW01_CLI_LINEARTOKENIZER_H
#define HW01_CLI_LINEARTOKENIZER_H

#include <tokenizers/ITokenizer.h>
#include <unordered_map>

// Implementation of tokenizer interface.
// Maintains specific symbols stored inside
// tokenizer : {|, =, $}
// This implementation suggests that
// the sequence of symbols with
// quotes at the end and front of the same
// is the one token. Moreover, it is impossible
// situation, when there are more then two
// quotes, which are equal to the enclosing quotes.
// At the very end tokenizer will return END token,
// which shows that it is the very last token in the string.
// Using tokenizer after returning END token may cause
// undefined behaviour.
class LinearTokenizer : public ITokenizer {
public:
    Token nextToken() override;

    bool hasNextToken() override;

    void append(const std::string &s) override;

    void clear() override;

private:
    std::string s = "";
    int pointer = 0;

    std::unordered_map<char, Token> specialSymbols = {
            {'|', Token(TokenType::PIPE, "|")},
            {'=', Token(TokenType::ASSIGN, "=")},
            {'$', Token(TokenType::DOLLAR, "$")}
    };
};


#endif //HW01_CLI_LINEARTOKENIZER_H
