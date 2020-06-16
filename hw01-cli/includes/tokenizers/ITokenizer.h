#ifndef HW01_CLI_ITOKENIZER_H
#define HW01_CLI_ITOKENIZER_H

#include <tokenizers/Token.h>
#include <string>

// Interface for tokenizers.
// The main goal for tokenizer is to split string
// into tokens using specific rules.
class ITokenizer {
public:
    // Add string to the end of current string
    // stored in tokenizer
    virtual void append(const std::string &s) = 0;

    // Make stored string empty
    virtual void clear() = 0;

    // Process following part of string,
    // creates and returns token corresponding
    // to that part.
    virtual Token nextToken() = 0;

    // Checkes, whether there exists
    // one more token in the remaining string
    // stored in tokenizer
    virtual bool hasNextToken() = 0;

    virtual ~ITokenizer() = default;
};

#endif //HW01_CLI_ITOKENIZER_H
