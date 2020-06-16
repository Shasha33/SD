#include <executors/EchoExecutor.h>

Status EchoExecutor::execute(
        const Command &command,
        StringChannel &inputChannel,
        StringChannel &outputChannel
) const {

    const auto &arguments = command.getCommandArguments().strip().asTokensVector();

    for (size_t i = 0; i < arguments.size(); i++) {
        if (arguments[i].getTokenType() == TokenType::SPACE
            && (i == 0u || arguments[i - 1].getTokenType() == TokenType::SPACE)) {
            continue;
        }
        outputChannel.write(arguments[i].asString());
    }
    outputChannel.write("\n");

    return Status();
}
