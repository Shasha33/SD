#ifndef HW01_CLI_COMMAND_H
#define HW01_CLI_COMMAND_H

#include <commands/CommandName.h>
#include <commands/CommandArguments.h>
#include <FileTreeState.h>

// Entity for representing command.
// It has a name and arguments.
// It can be executed by command executors.
class Command {
public:
    Command() = default;

    Command(
            const CommandName &commandName,
            const CommandArguments &commandArguments,
            FileTreeState* fileTreeState
    );

    Command(
            const CommandName &commandName,
            const CommandArguments &commandArguments
    );

    const CommandName &getCommandName() const;

    const CommandArguments &getCommandArguments() const;

    const FileTreeState* getFileTreeState() const;

    // Concatenates command name and command arguments
    // string representations and returns concatenation.
    std::string asString() const;

private:
    CommandName commandName;
    CommandArguments commandArguments;
    FileTreeState* fileTreeState = nullptr;
};


#endif //HW01_CLI_COMMAND_H
