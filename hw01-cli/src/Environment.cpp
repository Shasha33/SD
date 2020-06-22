#include <Environment.h>

const ICommandExecutor &Environment::getCommandExecutorByCommandName(const CommandName &commandName) const {
    if (commandName.getName().empty()) {

    }
    const auto &executor = factory.getCommandExecutorByCommandName(commandName);
    if (executor.has_value()) {
        return *executor.value();
    } else {
        return *externalExecutor;
    }
}

Environment::Environment()
        : factory(), lastCommandExitCode(0),
          echoExecutor(new EchoExecutor()),
          exitExecutor(new ExitExecutor()),
          catExecutor(new CatExecutor()),
          pwdExecutor(new PWDExecutor()),
          wcExecutor(new WCExecutor()),
          externalExecutor(new ExternalExecutor()),
          emptyExecutor(new EmptyExecutor()),
          grepExecutor(new GrepExecutor()),
          lsExecutor(new LSExecutor()),
          cdExecutor(new CDExecutor()) {
    factory.registerExecutor(CommandName("echo"), echoExecutor);
    factory.registerExecutor(CommandName("exit"), exitExecutor);
    factory.registerExecutor(CommandName("cat"), catExecutor);
    factory.registerExecutor(CommandName("pwd"), pwdExecutor);
    factory.registerExecutor(CommandName("wc"), wcExecutor);
    factory.registerExecutor(CommandName(""), emptyExecutor);
    factory.registerExecutor(CommandName("grep"), grepExecutor);
    factory.registerExecutor(CommandName("ls"), lsExecutor);
    factory.registerExecutor(CommandName("cd"), cdExecutor);
}

void Environment::setVariableValue(const std::string &variableName, const std::string &variableValue) {
    variableNameToValue[variableName] = variableValue;
}

const std::string &Environment::getVariableValue(const std::string &variableName) {
    return variableNameToValue[variableName];
}

int Environment::getLastCommandExitCode() const {
    return lastCommandExitCode;
}

void Environment::setLastCommandExitCode(int lastCommandExitCode) {
    Environment::lastCommandExitCode = lastCommandExitCode;
}

