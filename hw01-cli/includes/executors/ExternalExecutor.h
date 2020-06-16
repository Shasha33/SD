#ifndef HW01_CLI_EXTERNALEXECUTOR_H
#define HW01_CLI_EXTERNALEXECUTOR_H

#include <executors/ICommandExecutor.h>

// Executor for outer commands
class ExternalExecutor : public ICommandExecutor {
public:
    // Takes the name and arguments of outer utility and runs it
    Status execute(
            const Command &command,
            StringChannel &inputChannel,
            StringChannel &outputChannel
    ) const override;
};


#endif //HW01_CLI_EXTERNALEXECUTOR_H
