#include <boost/test/unit_test.hpp>
#include <executors/LSExecutor.h>
#include <experimental/filesystem>
#include <executors/CDExecutor.h>

BOOST_AUTO_TEST_SUITE(CDExecutorSuite)

    BOOST_AUTO_TEST_CASE(moveToHome) {
        std::experimental::filesystem::create_directories("ls_test_temp_dir/1/2");

        FileTreeState fileTreeState("./ls_test_temp_dir");
        fileTreeState.changeCurrentDirectory("1/2");
        Command command(
                CommandName("cd"),
                CommandArguments({Token(TokenType::SPACE, " ")}),
                &fileTreeState);
        StringChannel inputChannel, outputChannel;
        Status status = CDExecutor().execute(command, inputChannel, outputChannel);

        BOOST_CHECK_EQUAL(0, status.getExitCode());
        BOOST_CHECK_EQUAL(fileTreeState.getHome(), fileTreeState.getCurrentDirectory());
        std::experimental::filesystem::remove_all("ls_test_temp_dir/1/2");
    }

    BOOST_AUTO_TEST_CASE(testOneDirectory) {
        std::experimental::filesystem::create_directories("ls_test_temp_dir/3");

        FileTreeState fileTreeState;
        Command command(
                CommandName("cd"),
                CommandArguments(
                        {
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "ls_test_temp_dir/3")
                        }),
                &fileTreeState);
        StringChannel inputChannel, outputChannel;
        Status status = CDExecutor().execute(command, inputChannel, outputChannel);

        BOOST_CHECK_EQUAL(0, status.getExitCode());

        BOOST_CHECK_EQUAL("ls_test_temp_dir/3", fileTreeState.getCurrentDirectory());
        std::experimental::filesystem::remove_all("ls_test_temp_dir/3");
    }

BOOST_AUTO_TEST_SUITE_END()


