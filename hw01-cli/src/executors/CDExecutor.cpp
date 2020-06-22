#include <executors/CDExecutor.h>
#include <filesystem>
namespace fs = std::filesystem;

Status CDExecutor::execute(const Command &command, StringChannel &inputStream, StringChannel &outputStream) const {
    const CommandArguments &commandArguments = command.getCommandArguments();
    int argumentsCount = commandArguments.countTokensWithType(TokenType::LITERAL);
    auto status = Status();
    if (argumentsCount > 1) {
        status.setExitCode(-1);
        status.setMessage("too many arguments for cd\n");
    } else if (argumentsCount == 1) {
        for (auto argument : commandArguments.asTokensVector())
        {
            if (argument.getTokenType() == TokenType::LITERAL) {
                auto path = command.getFileTreeState()->getPossibleNewDirectory(argument.asString());
                if (!fs::exists(path)) {
                    status.setExitCode(-1);
                    status.setMessage("the directory does not exist\n");
                } else if (!fs::is_directory(path)) {
                    status.setExitCode(-1);
                    status.setMessage("the path does not match any directory\n");
                } else {
                    command.getFileTreeState()->changeCurrentDirectory(path);
                }

                break;
            }
        }
    }
    else {
        command.getFileTreeState()->changeCurrentDirectoryToHome();
    }
    return status;
}
