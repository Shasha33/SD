#include <commands/CommandName.h>

const std::string &CommandName::getName() const {
    return name;
}

CommandName::CommandName(const std::string &name) : name(name) {}

bool CommandName::operator==(const CommandName &other) const {
    return this->getName() == other.getName();
}
