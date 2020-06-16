#ifndef HW01_CLI_STATUS_H
#define HW01_CLI_STATUS_H

#include <string>

enum ExitStatus {EXIT, STAY};

// Entity for execution result
// which contains information
// about successfulness of command execution
class Status {
public:
    Status() = default;

    bool isSuccess() const;

    ExitStatus getExitStatus() const;

    void setExitStatus(ExitStatus exitStatus);

    int getExitCode() const;

    void setExitCode(int statusCode);

    const std::string &getMessage() const;

    void setMessage(const std::string &message);

private:
    int exitCode = 0;
    std::string message = "";
    ExitStatus exitStatus = STAY;
};


#endif //HW01_CLI_STATUS_H
