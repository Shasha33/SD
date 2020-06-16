#ifndef HW01_CLI_EXITEXECUTOR_H
#define HW01_CLI_EXITEXECUTOR_H

#include <executors/ICommandExecutor.h>

// Implementation of exit command
class ExitExecutor : public ICommandExecutor {
public:

    // If there are no non-space arguments then zero
    // will be returned. Otherwise executors checks
    // whether or not there are exactly one non-space
    // argument. If yes then it will try to cast it
    // to integer and return.
    // If no then exception will be thrown.
    Status execute(
            const Command &command,
            StringChannel &inputStream,
            StringChannel &outputStream
    ) const override;
};


#endif //HW01_CLI_EXITEXECUTOR_H
