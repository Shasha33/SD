#include <Status.h>

bool Status::isSuccess() const {
    return exitCode == 0;
}

ExitStatus Status::getExitStatus() const {
    return exitStatus;
}

void Status::setExitStatus(ExitStatus exitStatus) {
    Status::exitStatus = exitStatus;
}

int Status::getExitCode() const {
    return exitCode;
}

void Status::setExitCode(int statusCode) {
    Status::exitCode = statusCode;
}

const std::string &Status::getMessage() const {
    return message;
}

void Status::setMessage(const std::string &message) {
    Status::message = message;
}
