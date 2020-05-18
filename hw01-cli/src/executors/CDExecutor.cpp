#include <executors/CDExecutor.h>

Status CDExecutor::execute(const Command &command, StringChannel &inputStream, StringChannel &outputStream) const {
    const CommandArguments &commandArguments = command.getCommandArguments();
    int argumentsCount = commandArguments.countTokensWithType(TokenType::LITERAL);
    auto status = Status();
    if (argumentsCount > 1) {
        status.setExitCode(-1);
        status.setMessage("too many arguments for cd");
    } else if (argumentsCount == 1) {
        for (auto argument : commandArguments.asTokensVector())
        {
            if (argument.getTokenType() == TokenType::LITERAL) {
                command.getFileTreeState()->changeCurrentDirectory(argument.asString());
                break;
            }
        }
    }
    else {
        command.getFileTreeState()->changeCurrentDirectoryToHome();
    }
    return Status();
}
