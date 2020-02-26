#ifndef HW01_CLI_LSEXECUTOR_H
#define HW01_CLI_LSEXECUTOR_H

#include <experimental/filesystem>
#include <executors/ICommandExecutor.h>

// Implementation of ls command
class LSExecutor : public ICommandExecutor {
public:
    // Prints given directory or current directory into
    // output channel
    Status execute(
            const Command &command,
            StringChannel &inputStream,
            StringChannel &outputStream
    ) const override;

private:
    void printOneDirectory(const std::experimental::filesystem::path& path, StringChannel &outputStream) const;
};


#endif //HW01_CLI_LSEXECUTOR_H
