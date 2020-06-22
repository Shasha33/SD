#ifndef HW01_CLI_SHELL_H
#define HW01_CLI_SHELL_H

#include <tokenizers/ITokenizer.h>
#include <processors/IProcessor.h>
#include <Environment.h>

// Main entity for shell which can be runned
// from anywhere
class Shell {
public:
    // Runs the shell
    int run();

    Shell();

    ~Shell();

private:
    IProcessor *processor;
    Environment *environment;
    FileTreeState* fileTreeState;
};


#endif //HW01_CLI_SHELL_H
