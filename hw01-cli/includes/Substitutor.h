#ifndef HW01_CLI_SUBSTITUTOR_H
#define HW01_CLI_SUBSTITUTOR_H

#include <string>
#include <Token.h>
#include <Environment.h>
#include <vector>
#include <ITokenizer.h>

class Substitutor {
public:
    static Token substitute(const Token &token, Environment &environment);

private:
    static std::string substitute(const std::vector<Token> &tokens, Environment &environment);

    static bool isSibstitution(
            const Token &dollarToken,
            const Token &variableNameToken
    );

    static bool isValidVariableNameToken(const Token &nameToken);

    static bool isValidVariableValueToken(const Token &valueToken);

    static bool isTokenAvailableForSubstitution(const Token &token);
};


#endif //HW01_CLI_SUBSTITUTOR_H
