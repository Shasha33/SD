#include <filesystem>
#include "executors/LSExecutor.h"

Status LSExecutor::execute(
        const Command &command,
        StringChannel &inputStream,
        StringChannel &outputStream
) const {

    using namespace std::experimental::filesystem;

    const CommandArguments &commandArguments = command.getCommandArguments();
    if (commandArguments.countTokensWithType(TokenType::LITERAL) > 0) {
        const auto &arguments = commandArguments.asTokensVector();

        for (const auto &argument : arguments) {
            if (argument.getTokenType() != TokenType::LITERAL) {
                continue;
            }
            printOneDirectory(argument.asString(), outputStream);
        }
    } else {
        const std::string currentDirectory = command.getFileTreeState()->getCurrentDirectory();
        printOneDirectory(currentDirectory, outputStream);
    }

    return Status();
}

void LSExecutor::printOneDirectory(const std::experimental::filesystem::path& path, StringChannel &outputStream) const {
    outputStream.write(path.string() + ":\n");
    for (const auto &entry : std::experimental::filesystem::directory_iterator(path)) {
        auto filepath = std::filesystem::relative(entry.path().string(), path.string());
        outputStream.write(filepath.string() + "\n");
    }
}

