#include <processors/LoopProcessor.h>
#include <commands/CommandBuilder.h>
#include <executors/ICommandExecutor.h>
#include <tokenizers/ITokenizer.h>
#include <tokenizers/LinearTokenizer.h>
#include <sstream>
#include <channels/StringChannel.h>
#include <Substitutor.h>

Response LoopProcessor::process(
        const std::string &s,
        Environment &environment
) {
    tokenizer->clear();
    tokenizer->append(s);

    CommandBuilder commandBuilder;
    Status lastCommandStatus;
    StringChannel inputChannel, outputChannel;

    if (s.empty()) {
        return Response(Status(), inputChannel);
    }

    for (; lastCommandStatus.isSuccess() && tokenizer->hasNextToken();) {

        Token token = tokenizer->nextToken();
        TokenType tokenType = token.getTokenType();

        if (tokenType == TokenType::PIPE || tokenType == TokenType::END) {
            std::string commandString = commandBuilder.buildCommandString();
            commandBuilder.clear();
            for (shortTermTokenizer->clear(), shortTermTokenizer->append(commandString);
                 shortTermTokenizer->hasNextToken();) {
                commandBuilder.appendToken(
                        LoopProcessor::removeOuterQuotes(
                                shortTermTokenizer->nextToken()
                        )
                );
            }
            Command command = commandBuilder.buildCommand();
            commandBuilder.clear();
            Status status = environment
                    .getCommandExecutorByCommandName(command.getCommandName())
                    .execute(command.getCommandArguments(), inputChannel, outputChannel);
            // TODO: add variable $? (last commands execution exit code)
            lastCommandStatus = status;

            std::swap(inputChannel, outputChannel);
            outputChannel.clear();
        } else {
            commandBuilder.appendToken(Substitutor::substitute(token, environment));
        }
    }

    return Response(lastCommandStatus, inputChannel);
}

LoopProcessor::~LoopProcessor() {
    delete tokenizer;
}

LoopProcessor::LoopProcessor()
        : tokenizer(new LinearTokenizer()),
          shortTermTokenizer(new LinearTokenizer()) {}

Token LoopProcessor::removeOuterQuotes(const Token &token) {
    std::optional<char> lastQuote;
    std::string content;
    for (char c : token.asString()) {
        if (c == '\'' || c == '"') {
            if (lastQuote.has_value()) {
                if (lastQuote.value() == c) {
                    lastQuote.reset();
                } else {
                    content.push_back(c);
                }
            } else {
                lastQuote = c;
            }
        } else {
            content.push_back(c);
        }
    }
    return Token(token.getTokenType(), content);
}
