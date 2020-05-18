#include <commands/Command.h>

const CommandName &Command::getCommandName() const {
    return commandName;
}

const CommandArguments &Command::getCommandArguments() const {
    return commandArguments;
}

FileTreeState* Command::getFileTreeState() const {
    return fileTreeState;
}

Command::Command(
        const CommandName &commandName,
        const CommandArguments &commandArguments,
        FileTreeState *fileTreeState
) : commandName(commandName), commandArguments(commandArguments), fileTreeState(fileTreeState) {}

std::string Command::asString() const {
    return getCommandName().getName() + getCommandArguments().asString();
}

Command::Command(
        const CommandName &commandName,
        const CommandArguments &commandArguments
) : commandName(commandName), commandArguments(commandArguments) {}
