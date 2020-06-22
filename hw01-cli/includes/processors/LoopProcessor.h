#ifndef HW01_CLI_LOOPPROCESSOR_H
#define HW01_CLI_LOOPPROCESSOR_H

#include <processors/IProcessor.h>

// Implementation of command line processor
class LoopProcessor : public IProcessor {
public:
    LoopProcessor();

    // Takes command, splits by pipe symbol
    // runs command one by one from left to right.
    // Uses output channel from the previous command
    // as input channel for the nex command.
    // If some command returns non-success result
    // then processing will be terminated.
    // Exit code of last command will be stored
    // in environmental variable '?'
    Response process(
            const std::string &s,
            Environment &environment,
            FileTreeState &fileTreeState
    ) override;

    ~LoopProcessor() override;

protected:
    Response process(
            const std::string &s,
            Environment &environment
    );

private:
    static Token removeOuterQuotes(const Token &token);

private:
    ITokenizer *tokenizer;
    ITokenizer *shortTermTokenizer;
};


#endif //HW01_CLI_LOOPPROCESSOR_H
