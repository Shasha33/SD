#ifndef HW01_CLI_FILETREESTATE_H
#define HW01_CLI_FILETREESTATE_H

#include <string>

class FileTreeState {
public:
    FileTreeState();
    explicit FileTreeState(std::string home);

    std::string getHome() const;
    void changeCurrentDirectory(std::string dir);
    std::string getCurrentDirectory() const;

private:
    const std::string homeDirectory;
    std::string currentDirectory = homeDirectory;
};

#endif //HW01_CLI_FILETREESTATE_H
