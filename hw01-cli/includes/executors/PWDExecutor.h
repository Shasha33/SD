#ifndef HW01_CLI_PWDEXECUTOR_H
#define HW01_CLI_PWDEXECUTOR_H

#include <executors/ICommandExecutor.h>

// Implementation of pwd command
class PWDExecutor : public ICommandExecutor {
public:
    // Writes current working directory into
    // output channel
    Status execute(
            const Command &command,
            StringChannel &inputStream,
            StringChannel &outputStream
    ) const override;
};


#endif //HW01_CLI_PWDEXECUTOR_H
