#include <executors/CDExecutor.h>
#include <iostream>

Status CDExecutor::execute(const Command &command, StringChannel &inputStream, StringChannel &outputStream) const {
    const CommandArguments &commandArguments = command.getCommandArguments();
    int argumentsCount = commandArguments.countTokensWithType(TokenType::LITERAL);
    FileTreeState *fileTreeState = const_cast<FileTreeState *>(command.getFileTreeState());
    if (argumentsCount > 0) {
        for (auto argument : commandArguments.asTokensVector())
        {
            outputStream.write(argument.asString() + "\n");
            if (argument.getTokenType() == TokenType::LITERAL) {
                fileTreeState->changeCurrentDirectory(argument.asString());
                break;
            }
        }
    } else {
        fileTreeState->changeCurrentDirectoryToHome();
    }
    return Status();
}
