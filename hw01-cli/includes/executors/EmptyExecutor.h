#ifndef HW01_CLI_EMPTYEXECUTOR_H
#define HW01_CLI_EMPTYEXECUTOR_H

#include <executors/ICommandExecutor.h>

// Executor for empty line of line only with space characters
class EmptyExecutor : public ICommandExecutor {
public:
    // Do nothing
    Status execute(
            const Command &command,
            StringChannel &inputChannel,
            StringChannel &outputChannel
    ) const override;
};


#endif //HW01_CLI_EMPTYEXECUTOR_H
