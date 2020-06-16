#ifndef HW01_CLI_RESPONSE_H
#define HW01_CLI_RESPONSE_H

#include <sstream>
#include <Status.h>
#include <channels/StringChannel.h>

// Entity for processor returned result
// which contains status and final output channel
class Response {
public:
    Response(const Status &status, const StringChannel &stringChannel);

    const Status &getStatus() const;

    const StringChannel &getStringChannel() const;

private:
    Status status;
    StringChannel stringChannel;
};


#endif //HW01_CLI_RESPONSE_H
