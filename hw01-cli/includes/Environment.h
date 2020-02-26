#ifndef HW01_CLI_ENVIRONMENT_H
#define HW01_CLI_ENVIRONMENT_H

#include <commands/CommandExecutorFactory.h>
#include <commands/Command.h>
#include <commands/CommandName.h>

#include <unordered_map>
#include <string>

#include <executors/EchoExecutor.h>
#include <executors/ExitExecutor.h>
#include <executors/CatExecutor.h>
#include <executors/PWDExecutor.h>
#include <executors/WCExecutor.h>
#include <executors/ExternalExecutor.h>
#include <executors/EmptyExecutor.h>
#include <executors/grep/GrepExecutor.h>
#include <executors/LSExecutor.h>

// Entity for storing inner shell variables and
// command which are implemented in shell
class Environment {
public:
    Environment();

    // Determines the executor for command by its name
    const ICommandExecutor &getCommandExecutorByCommandName(
            const CommandName &commandName
    ) const;

    const std::string &getVariableValue(const std::string &variableName);

    void setVariableValue(const std::string &variableName, const std::string &variableValue);

    int getLastCommandExitCode() const;

    void setLastCommandExitCode(int lastCommandExitCode);

private:
    CommandExecutorFactory factory;
    std::unordered_map<std::string, std::string> variableNameToValue;

    int lastCommandExitCode = 0;

    EchoExecutor *echoExecutor;
    ExitExecutor *exitExecutor;
    CatExecutor *catExecutor;
    PWDExecutor *pwdExecutor;
    WCExecutor *wcExecutor;
    ExternalExecutor *externalExecutor;
    EmptyExecutor *emptyExecutor;
    GrepExecutor *grepExecutor;
    LSExecutor *lsExecutor;
};

#endif //HW01_CLI_ENVIRONMENT_H
