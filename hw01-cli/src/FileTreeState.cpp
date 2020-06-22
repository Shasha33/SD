#include <filesystem>
#include "FileTreeState.h"

std::string FileTreeState::getHome() const {
    return homeDirectory;
}

std::string FileTreeState::getCurrentDirectory() const {
    return currentDirectory;
}

FileTreeState::FileTreeState() : homeDirectory(".") {}

std::string FileTreeState::getPossibleNewDirectory(const std::string& dir) {
    auto currentDirectoryCopy = currentDirectory;
    if (currentDirectoryCopy.back() != '/') {
        currentDirectoryCopy += '/';
    }

    if (dir[0] == '/') {
        currentDirectoryCopy = dir;
    } else {
        currentDirectoryCopy += dir;
    }

    return std::filesystem::canonical(currentDirectoryCopy);
}

void FileTreeState::changeCurrentDirectory(const std::string& dir) {
    currentDirectory = std::filesystem::absolute(getPossibleNewDirectory(dir));
}

FileTreeState::FileTreeState(const std::string& home) : homeDirectory(home) {}

void FileTreeState::changeCurrentDirectoryToHome() {
    currentDirectory = homeDirectory;
}
