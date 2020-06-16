#include "Response.h"

Response::Response(const Status &status, const StringChannel &stringChannel)
        : status(status), stringChannel(stringChannel) {}

const Status &Response::getStatus() const {
    return status;
}

const StringChannel &Response::getStringChannel() const {
    return stringChannel;
}
