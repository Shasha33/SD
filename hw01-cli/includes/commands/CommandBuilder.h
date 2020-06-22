#ifndef HW01_CLI_COMMANDBUILDER_H
#define HW01_CLI_COMMANDBUILDER_H

#include <tokenizers/Token.h>
#include <commands/Command.h>
#include <vector>
#include <Environment.h>

// Entity for building command
// by appending new tokens.
// The first token should be LITERAL
// and should contains a command name
// others tokens will be correspond
// to the arguments part.
class CommandBuilder {
public:
    CommandBuilder() = default;
    CommandBuilder(FileTreeState* fileTreeState);

    // Add token to the end of token
    // sequence. If there are no any tokens
    // yet and new token is not LITERAL or it
    // token content is empty then such token
    // will be skipped.
    void appendToken(const Token &token);

    // Clears set of appended tokens
    void clear();

    // Takes the first token as command name.
    // Others token will be used for command
    // arguments. If there is no tokens
    Command buildCommand() const;

    // Builds string representation of command
    // as concatenation of all tokens string
    // representation and returns it.
    std::string buildCommandString() const;

private:
    std::vector<Token> tokens;
    FileTreeState* fileTreeState = nullptr;
};


#endif //HW01_CLI_COMMANDBUILDER_H
