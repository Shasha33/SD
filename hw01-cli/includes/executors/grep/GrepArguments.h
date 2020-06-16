#ifndef HW01_CLI_ARGV_H
#define HW01_CLI_ARGV_H

#include <commands/Command.h>

// Wrapper for command line arguments parser
class GrepArguments {
public:
    explicit GrepArguments(const Command &command);

    ~GrepArguments();

    bool isCaseInsensitivity() const;

    bool isSearchOnlyWords() const;

    unsigned int getLinesNumberToPrint() const;

    const std::string &getRegexp() const;

    const std::vector<std::string> &getFiles() const;

private:
    int argc;
    char **argv;

    bool caseInsensitivity;
    bool searchOnlyWords;
    unsigned int nLinesToPrint;
    std::string regexp;
    std::vector<std::string> files;
};


#endif //HW01_CLI_ARGV_H
