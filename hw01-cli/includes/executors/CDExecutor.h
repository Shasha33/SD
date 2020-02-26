#ifndef HW01_CLI_CDEXECUTOR_H
#define HW01_CLI_CDEXECUTOR_H

#include <experimental/filesystem>
#include <executors/ICommandExecutor.h>

// Implementation of cd command
class CDExecutor : public ICommandExecutor {
public:
    // Changes current directory value to the argument
    // With empty args reverts current directory to home directory
    Status execute(
            const Command &command,
            StringChannel &inputStream,
            StringChannel &outputStream
    ) const override;

};

#endif //HW01_CLI_CDEXECUTOR_H
