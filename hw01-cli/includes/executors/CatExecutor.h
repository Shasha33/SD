#ifndef HW01_CLI_CATEXECUTOR_H
#define HW01_CLI_CATEXECUTOR_H

#include <executors/ICommandExecutor.h>
#include <optional>

// cat utility executor
class CatExecutor : public ICommandExecutor {
public:
    // Reads files and writes the data from the files
    // to the output channel
    Status execute(
            const Command &command,
            StringChannel &inputStream,
            StringChannel &outputStream
    ) const override;
private:
    Status executeNoArgumentsMode(
            const CommandArguments &commandArguments,
            StringChannel &inputChannel,
            StringChannel &outputChannel
    ) const;

    Status executeAtLeastOneArgumentMode(
            const CommandArguments &commandArguments,
            StringChannel &inputChannel,
            StringChannel &outputChannel
    ) const;
};


#endif //HW01_CLI_CATEXECUTOR_H
