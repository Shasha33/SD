#ifndef HW01_CLI_FILETREESTATE_H
#define HW01_CLI_FILETREESTATE_H

#include <string>

/// Stores current position in file tree and initial home path
/// Default home is .
class FileTreeState {
public:
    FileTreeState();
    explicit FileTreeState(const std::string& home);

    std::string getHome() const;
    void changeCurrentDirectory(const std::string& dir);
    void changeCurrentDirectoryToHome();
    std::string getCurrentDirectory() const;

private:
    const std::string homeDirectory;
    std::string currentDirectory = homeDirectory;
};

#endif //HW01_CLI_FILETREESTATE_H
