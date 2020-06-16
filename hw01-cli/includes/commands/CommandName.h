#ifndef HW01_CLI_COMMANDNAME_H
#define HW01_CLI_COMMANDNAME_H

#include <string>

// Wrapper for command name
class CommandName {
public:
    CommandName() = default;

    explicit CommandName(const std::string &name);

    const std::string &getName() const;

    bool operator==(const CommandName &other) const;

private:
    std::string name;
};


#endif //HW01_CLI_COMMANDNAME_H
