#include <executors/EmptyExecutor.h>

Status EmptyExecutor::execute(
        const Command &command,
        StringChannel &inputChannel,
        StringChannel &outputChannel
) const {
    return Status();
}
