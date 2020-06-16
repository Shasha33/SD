#ifndef HW01_CLI_IPROCESSOR_H
#define HW01_CLI_IPROCESSOR_H

#include <Response.h>
#include <tokenizers/ITokenizer.h>
#include <string>
#include <Environment.h>

// Interface for entity which will
// process command represented in string line
class IProcessor {
public:
    // Takes a string which is a command
    // and process it using its own policy
    virtual Response process(
            const std::string &s,
            Environment &environment
    ) = 0;

    virtual ~IProcessor() = default;
};


#endif //HW01_CLI_IPROCESSOR_H
