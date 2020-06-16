#ifndef HW01_CLI_UTILEXECUTORFACTORY_H
#define HW01_CLI_UTILEXECUTORFACTORY_H

#include <string>
#include <executors/ICommandExecutor.h>
#include <commands/CommandName.h>
#include <unordered_map>
#include <map>
#include <vector>
#include <optional>

// Entity for registering and giving commands by its name.
// All commands to be registered should implement
// ICommandExecutor interface.
class CommandExecutorFactory {
public:
    // Adds given command executor with given name
    // to the list of registered command.
    // If there are several commands with the same
    // name then get method may returns any of them.
    void registerExecutor(
            const CommandName &commandName,
            ICommandExecutor *commandExecutor
    );

    // Gives an instance of command executor by given name.
    // If there is no command executor with given name
    // then std::optional without value will be returned.
    std::optional<ICommandExecutor *const> getCommandExecutorByCommandName(
            const CommandName &commandName
    ) const;

private:
    std::vector<std::pair<CommandName, ICommandExecutor *const >> nameToExecutorMap;
};

#endif //HW01_CLI_UTILEXECUTORFACTORY_H
