#include <filesystem>
#include "FileTreeState.h"

std::string FileTreeState::getHome() const {
    return homeDirectory;
}

std::string FileTreeState::getCurrentDirectory() const {
    return currentDirectory;
}

FileTreeState::FileTreeState() : homeDirectory(".") {}


void FileTreeState::changeCurrentDirectory(const std::string& dir) {
    if (currentDirectory.back() != '/') {
        currentDirectory += '/';
    }

    if (dir[0] == '/') {
        currentDirectory = dir;
    } else {
        currentDirectory += dir;
    }

    currentDirectory = std::filesystem::relative(currentDirectory, homeDirectory);
}

FileTreeState::FileTreeState(const std::string& home) : homeDirectory(home) {}

void FileTreeState::changeCurrentDirectoryToHome() {
    currentDirectory = homeDirectory;
}
