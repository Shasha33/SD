#include <executors/ExternalExecutor.h>
#include <boost/process.hpp>
#include <sstream>

namespace bp = boost::process;

Status ExternalExecutor::execute(
        const Command &command,
        StringChannel &inputChannel,
        StringChannel &outputChannel
) const {

    Status status;
    std::stringstream stringstream;
    bp::ipstream out_ipstream, err_ipstream;
    bp::opstream opstream;

    std::error_code errorCode;
    bp::child childProcess(
            command.asString(),
            errorCode,
            bp::std_out > out_ipstream,
            bp::std_err > err_ipstream,
            bp::std_in < opstream
    );

    while (!inputChannel.empty()) {
        opstream << inputChannel.read();
    }
    opstream.flush();
    opstream.pipe().close();

    childProcess.wait();

    status.setExitCode(errorCode.value());
    status.setMessage(errorCode.message() + "\n");

    for (char c; out_ipstream.get(c);) {
        outputChannel.write(c);
    }

    for (char c; err_ipstream.get(c);) {
        outputChannel.write(c);
    }

    return status;
}
