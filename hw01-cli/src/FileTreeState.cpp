#include "FileTreeState.h"

#include <utility>

std::string FileTreeState::getHome() const{
    return homeDirectory;
}

std::string FileTreeState::getCurrentDirectory() const {
    return currentDirectory;
}

FileTreeState::FileTreeState() : homeDirectory(".") {}


void FileTreeState::changeCurrentDirectory(std::string dir) {
    if (dir[0] == '/') {
        currentDirectory = dir;
    } else {
        currentDirectory += dir;
    }

    if (currentDirectory.back() != '/') {
        currentDirectory += '/';
    }
}

FileTreeState::FileTreeState(std::string home) : homeDirectory(std::move(home)) {}
