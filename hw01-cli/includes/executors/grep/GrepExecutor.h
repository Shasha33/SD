#ifndef HW01_CLI_GREPEXECUTOR_H
#define HW01_CLI_GREPEXECUTOR_H

#include <executors/ICommandExecutor.h>
#include <executors/grep/GrepArguments.h>
#include <regex>

// grep utility executor
class GrepExecutor : public ICommandExecutor {
public:
    // Prints lines which are matched with given regular expression
    Status execute(
            const Command &command,
            StringChannel &inputChannel,
            StringChannel &outputChannel
    ) const override;

private:
    Status executeFromChannelMode(
            StringChannel &inputChannel,
            StringChannel &outputChannel,
            const GrepArguments &arguments
    ) const;

private:
    const std::regex wordRegex = std::regex("\\w+");
};


#endif //HW01_CLI_GREPEXECUTOR_H
