#include <Substitutor.h>
#include <tokenizers/LinearTokenizer.h>

bool Substitutor::isValidVariableName(const std::string &name) {
    if (name.empty()) {
        return false;
    }
    if (!std::isalpha(name.front())) {
        return false;
    }
    for (size_t i = 1; i < name.size(); i++) {
        if (!(std::isalpha(name[i]) || std::isdigit(name[i]))) {
            return false;
        }
    }
    return true;
}

bool Substitutor::isSibstitution(const Token &dollarToken, const Token &variableNameToken) {
    return dollarToken.getTokenType() == TokenType::DOLLAR
           && (isValidVariableName(variableNameToken.asString()) || variableNameToken.asString() == "?");
}

std::string Substitutor::substitute(const std::vector<Token> &tokens, Environment &environment) {
    std::string substitution;
    for (size_t i = 0; i < tokens.size();) {
        if (i + 1 < tokens.size() && Substitutor::isSibstitution(tokens[i], tokens[i + 1])) {
            std::string variableName = tokens[i + 1].asString();
            if (variableName == "?") {
                substitution += std::to_string(environment.getLastCommandExitCode());
            } else {
                substitution += environment.getVariableValue(variableName);
            }
            i += 2;
        } else {
            substitution += tokens[i].asString();
            i++;
        }
    }
    return substitution;
}

bool Substitutor::isTokenAvailableForSubstitution(const Token &token) {
    // substitution can be only between two outer quotes '\"'
    if (token.getTokenType() != TokenType::LITERAL) {
        return false;
    }
    const auto &stringToken = token.asString();
    return stringToken.size() > 1u && stringToken.front() == '"' && stringToken.back() == '"';
}

Token Substitutor::substitute(const Token &token, Environment &environment) {
    if (!isTokenAvailableForSubstitution(token)) {
        return token;
    }
    std::string s = token.asString();
    s = std::string(s.begin() + 1, s.end() - 1); // remove outer quotes
    LinearTokenizer tokenizer;
    tokenizer.append(s);
    std::vector<Token> tokens;
    while (tokenizer.hasNextToken()) {
        tokens.push_back(tokenizer.nextToken());
    }
    return Token(token.getTokenType(), "\"" + Substitutor::substitute(tokens, environment) + "\"");
}

bool Substitutor::tryAssign(const Command &command, Environment &environment) {
    std::vector<Token> tokens = command.getCommandArguments().rstrip().asTokensVector();
    if (tokens.size() != 2u) {
        return false;
    }
    Token assignmentToken = tokens[0];
    if (assignmentToken.getTokenType() != TokenType::ASSIGN) {
        return false;
    }
    std::string variableName = command.getCommandName().getName();
    if (!isValidVariableName(variableName)) {
        return false;
    }
    std::string variableValue = tokens[1].asString();
    environment.setVariableValue(variableName, variableValue);
    return true;
}
