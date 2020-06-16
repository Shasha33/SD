#ifndef HW01_CLI_UTILEXECUTOR_H
#define HW01_CLI_UTILEXECUTOR_H

#include <Status.h>
#include <commands/Command.h>
#include <channels/StringChannel.h>

// Interface for command executors.
class ICommandExecutor {
public:
    // Reads data from inputs channel,
    // Write data into output channel,
    // Executes, returns status with
    // all important information
    // such as exit code, message,
    // exit status, etc.
    virtual Status execute(
            const Command &command,
            StringChannel &inputChannel,
            StringChannel &outputChannel
    ) const = 0;

    virtual ~ICommandExecutor() = default;
};


#endif //HW01_CLI_UTILEXECUTOR_H
