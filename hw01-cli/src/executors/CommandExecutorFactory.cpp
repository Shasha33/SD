#include <commands/CommandExecutorFactory.h>

void CommandExecutorFactory::registerExecutor(
        const CommandName &commandName,
        ICommandExecutor *const commandExecutor) {
    nameToExecutorMap.emplace_back(commandName, commandExecutor);
}

std::optional<ICommandExecutor * const> CommandExecutorFactory::getCommandExecutorByCommandName(
        const CommandName &commandName
) const {
    for (const auto &item : nameToExecutorMap) {
        if (item.first == commandName) {
            return std::optional<ICommandExecutor *const>(item.second);
        }
    }
    return std::optional<ICommandExecutor *const>();
}
