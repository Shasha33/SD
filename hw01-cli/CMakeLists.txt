cmake_minimum_required(VERSION 3.10)
project(hw01_cli)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-pthread")

add_library(
        cli

        STATIC

        src/Shell.cpp
        includes/Shell.h

        src/Environment.cpp
        includes/Environment.h

        #       ========================
        src/executors/ICommandExecutor.cpp
        includes/executors/ICommandExecutor.h

        src/executors/CommandExecutorFactory.cpp
        includes/commands/CommandExecutorFactory.h

        src/executors/EchoExecutor.cpp
        includes/executors/EchoExecutor.h

        src/executors/ExitExecutor.cpp
        includes/executors/ExitExecutor.h

        src/executors/CatExecutor.cpp
        includes/executors/CatExecutor.h

        src/executors/PWDExecutor.cpp
        includes/executors/PWDExecutor.h

        src/executors/WCExecutor.cpp
        includes/executors/WCExecutor.h

        src/executors/ExternalExecutor.cpp
        includes/executors/ExternalExecutor.h

        src/executors/EmptyExecutor.cpp
        includes/executors/EmptyExecutor.h

        src/executors/LSExecutor.cpp
        includes/executors/LSExecutor.h

        src/executors/grep/GrepExecutor.cpp
        includes/executors/grep/GrepExecutor.h

        src/executors/grep/GrepArguments.cpp
        includes/executors/grep/GrepArguments.h

        #       ========================
        includes/processors/IProcessor.h

        src/processors/LoopProcessor.cpp
        includes/processors/LoopProcessor.h

        src/Status.cpp
        includes/Status.h

        src/Response.cpp
        includes/Response.h

        #       ========================
        src/commands/Command.cpp
        includes/commands/Command.h

        src/commands/CommandName.cpp
        includes/commands/CommandName.h

        src/commands/CommandArguments.cpp
        includes/commands/CommandArguments.h

        src/commands/CommandBuilder.cpp
        includes/commands/CommandBuilder.h

        src/FileTreeState.cpp
        includes/FileTreeState.h

        #       ========================
        includes/tokenizers/ITokenizer.h

        src/tokenizers/LinearTokenizer.cpp
        includes/tokenizers/LinearTokenizer.h

        src/tokenizers/Token.cpp
        includes/tokenizers/Token.h

        #       ========================
        includes/channels/IInputChannel.h
        includes/channels/IOutputChannel.h

        src/channels/StringChannel.cpp
        includes/channels/StringChannel.h

        #       ========================
        src/Substitutor.cpp
        includes/Substitutor.h

        #       ========================
        cxxopts/include/cxxopts.hpp
)

add_executable(
        hw01_cli

        src/main.cpp
)

target_link_libraries(
        hw01_cli
        stdc++fs
        cli
)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
include_directories(${Boost_INCLUDE_DIRS})
find_package(Boost COMPONENTS system filesystem REQUIRED)

target_link_libraries(
        hw01_cli

        Boost::system
        Boost::filesystem

        stdc++fs
)

include_directories(src)
include_directories(includes)
include_directories(cxxopts/include)

add_subdirectory(test)
