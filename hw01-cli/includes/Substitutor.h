#ifndef HW01_CLI_SUBSTITUTOR_H
#define HW01_CLI_SUBSTITUTOR_H

#include <string>
#include <tokenizers/Token.h>
#include <Environment.h>
#include <vector>
#include <tokenizers/ITokenizer.h>

// Entity without state, the main task of which
// is substitution and assign operations.
class Substitutor {
public:

    // Tries to substitute variables values instead of $name constructions
    // using given environment.
    // Substitution can be made only in token with weak quotes at both ends.
    static Token substitute(const Token &token, Environment &environment);

    // Checks, whether or not command is the substitution command
    // If no then false will be returned
    // If yes then assignment will be made and new variable value
    // will be stored in the given environment.
    static bool tryAssign(const Command &command, Environment &environment);

private:
    static std::string substitute(const std::vector<Token> &tokens, Environment &environment);

    static bool isSibstitution(
            const Token &dollarToken,
            const Token &variableNameToken
    );

    static bool isValidVariableName(const std::string &name);

    static bool isTokenAvailableForSubstitution(const Token &token);
};


#endif //HW01_CLI_SUBSTITUTOR_H
