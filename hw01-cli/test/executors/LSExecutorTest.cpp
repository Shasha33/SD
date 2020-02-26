#include <boost/test/unit_test.hpp>
#include <executors/LSExecutor.h>
#include <experimental/filesystem>
BOOST_AUTO_TEST_SUITE(LSExecutorSuite)

    BOOST_AUTO_TEST_CASE(testCurrentDirectory) {
        std::experimental::filesystem::create_directories("ls_test_temp_dir/1/2");
        std::experimental::filesystem::create_directories("ls_test_temp_dir/3");

        FileTreeState fileTreeState("./ls_test_temp_dir");
        Command command(
                CommandName("ls"),
                CommandArguments({Token(TokenType::SPACE, " ")}),
                &fileTreeState);
        StringChannel inputChannel, outputChannel;
        Status status = LSExecutor().execute(command, inputChannel, outputChannel);

        BOOST_CHECK_EQUAL(0, status.getExitCode());

        BOOST_CHECK_EQUAL("./ls_test_temp_dir:\n./ls_test_temp_dir/3\n./ls_test_temp_dir/1\n", outputChannel.read());
        std::experimental::filesystem::remove_all("ls_test_temp_dir/1/2");
        std::experimental::filesystem::remove_all("ls_test_temp_dir/3");
    }

    BOOST_AUTO_TEST_CASE(testOneDirectory) {
        std::experimental::filesystem::create_directories("ls_test_temp_dir/1/2");
        std::experimental::filesystem::create_directories("ls_test_temp_dir/3");

        FileTreeState fileTreeState;
        Command command(
                CommandName("ls"),
                CommandArguments({Token(TokenType::SPACE, " "), Token(TokenType::LITERAL, "ls_test_temp_dir/3")}),
                &fileTreeState);
        StringChannel inputChannel, outputChannel;
        Status status = LSExecutor().execute(command, inputChannel, outputChannel);

        BOOST_CHECK_EQUAL(0, status.getExitCode());

        BOOST_CHECK_EQUAL("ls_test_temp_dir/3:\n", outputChannel.read());
        std::experimental::filesystem::remove_all("ls_test_temp_dir/1/2");
        std::experimental::filesystem::remove_all("ls_test_temp_dir/3");
    }

    BOOST_AUTO_TEST_CASE(testTwoDirectories) {
        std::experimental::filesystem::create_directories("ls_test_temp_dir/1/2");
        std::experimental::filesystem::create_directories("ls_test_temp_dir/3");

        FileTreeState fileTreeState;
        Command command(
                CommandName("ls"),
                CommandArguments({
                    Token(TokenType::SPACE, " "),
                    Token(TokenType::LITERAL, "ls_test_temp_dir/3"),
                    Token(TokenType::SPACE, " "),
                    Token(TokenType::LITERAL, "ls_test_temp_dir/1/2")}),
                &fileTreeState);
        StringChannel inputChannel, outputChannel;
        Status status = LSExecutor().execute(command, inputChannel, outputChannel);

        BOOST_CHECK_EQUAL(0, status.getExitCode());

        BOOST_CHECK_EQUAL("ls_test_temp_dir/3:\nls_test_temp_dir/1/2:\n", outputChannel.read());
        std::experimental::filesystem::remove_all("ls_test_temp_dir/1/2");
        std::experimental::filesystem::remove_all("ls_test_temp_dir/3");
    }

BOOST_AUTO_TEST_SUITE_END()

