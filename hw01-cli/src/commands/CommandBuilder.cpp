#include <iostream>
#include <commands/CommandBuilder.h>
#include <assert.h>
#include <algorithm>

CommandBuilder::CommandBuilder(FileTreeState* fileTreeState) : fileTreeState(fileTreeState) {}

void CommandBuilder::appendToken(const Token &token) {
    if (!token.empty()
        && !(tokens.empty() && token.getTokenType() != TokenType::LITERAL)) {
        tokens.push_back(token);
    }
}

void CommandBuilder::clear() {
    tokens.clear();
}

Command CommandBuilder::buildCommand() const {
    if (tokens.empty()) {
        return Command();
    }
    return Command(
            CommandName(tokens.front().asString()),
            CommandArguments(std::vector<Token>(tokens.begin() + 1, tokens.end())),
            fileTreeState
    );
}

std::string CommandBuilder::buildCommandString() const {
    std::string commandString;
    for (const auto &token : tokens) {
        commandString += token.asString();
    }
    return commandString;
}

