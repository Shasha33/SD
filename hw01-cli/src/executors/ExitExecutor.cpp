#include <executors/ExitExecutor.h>
#include <assert.h>
#include <stdexcept>

Status ExitExecutor::execute(
        const Command &command,
        StringChannel &inputStream,
        StringChannel &outputStream
) const {
    int goodArgumentsCount = 0, exitCode = 0;
    for (const auto &argument : command.getCommandArguments().asTokensVector()) {
        const auto &type = argument.getTokenType();
        if (type != TokenType::END && type != TokenType::SPACE) {
            goodArgumentsCount++;
            if (goodArgumentsCount > 1) {
                throw std::invalid_argument("Too many arguments");
            }
            exitCode = std::stoi(argument.asString());
        }
    }
    Status status;
    status.setExitStatus(ExitStatus::EXIT);
    status.setExitCode(exitCode);
    return status;
}
