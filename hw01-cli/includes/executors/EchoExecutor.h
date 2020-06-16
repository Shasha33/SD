#ifndef HW01_CLI_ECHOEXECUTOR_H
#define HW01_CLI_ECHOEXECUTOR_H

#include <executors/ICommandExecutor.h>

// Implementation of echo command
class EchoExecutor : public ICommandExecutor {
public:
    // Removes all space tokens from the ends of arguments list
    // and writes all remaining arguments into the output channel
    // in the same order. Serial of spaces will be compressed into one
    // space character.
    Status execute(
            const Command &command,
            StringChannel &inputChannel,
            StringChannel &outputChannel
    ) const override;

};


#endif //HW01_CLI_ECHOEXECUTOR_H
