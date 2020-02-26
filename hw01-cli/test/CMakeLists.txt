cmake_minimum_required(VERSION 3.10)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

include_directories(${Boost_INCLUDE_DIR})
include_directories(${BOOST_ROOT})

add_definitions(-DBOOST_TEST_DYN_LINK)

set(CMAKE_CXX_FLAGS "-pthread")

add_executable(
        hw01_cli_tests

        main.cpp

        channels/StringChannelTest.cpp
        tokenizers/TokenTest.cpp
        tokenizers/LinearTokenizerTest.cpp

        commands/CommandArgumentsTest.cpp
        commands/CommandNameTest.cpp
        commands/CommandTest.cpp
        commands/CommandBuilderTest.cpp

        SubstitutorTest.cpp

        executors/CommandExecutorFactoryTest.cpp
        executors/CatExecutorTest.cpp
        executors/EchoExecutorTest.cpp
        executors/ExitExecutorTest.cpp
        executors/WCExecutorTest.cpp
        executors/grep/GrepExecutorTest.cpp
        executors/grep/GrepArgumentsTest.cpp
        executors/LSExecutorTest.cpp

        processors/LoopProcessorTest.cpp
)

target_link_libraries(
        hw01_cli_tests
        cli

        Boost::unit_test_framework

        stdc++fs
        boost_system
)

FILE(COPY resources/wc_test_file.txt DESTINATION resources)
FILE(COPY resources/wc_test_file2.txt DESTINATION resources)
FILE(COPY resources/grep_file.txt DESTINATION resources)

enable_testing()
add_test(cli_unit_tests hw01_cli_tests)
