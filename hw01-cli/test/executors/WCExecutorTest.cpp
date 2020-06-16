#include <boost/test/unit_test.hpp>
#include <executors/WCExecutor.h>
#include <channels/StringChannel.h>

#include <iostream>
#include <executors/ExternalExecutor.h>

BOOST_AUTO_TEST_SUITE(WCExecutorSuite)

    BOOST_AUTO_TEST_CASE(textExecuteEmptyArgumentsMode) {
        WCExecutor wcExecutor;
        StringChannel inputChannel, outputChannel;
        Command command = Command(CommandName("wc"), CommandArguments());
        inputChannel.write("123\n456 789");
        Status status = wcExecutor.execute(command, inputChannel, outputChannel);
        std::string expectedOutput = "1 3 11\n";
        BOOST_CHECK_EQUAL(expectedOutput, outputChannel.read());
    }

    BOOST_AUTO_TEST_CASE(textExecuteFileReadMode) {
        WCExecutor wcExecutor;
        StringChannel inputChannel, outputChannel;
        Command command = Command(
                CommandName("wc"),
                CommandArguments(
                        {
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "resources/wc_test_file.txt"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "resources/wc_test_file2.txt")
                        }
                )
        );

        Status status = wcExecutor.execute(command, inputChannel, outputChannel);
        std::string expectedOutput = "5 9 29 resources/wc_test_file.txt\n"
                                     "16 34 108 resources/wc_test_file2.txt\n"
                                     "21 43 137 total\n";
        BOOST_CHECK_EQUAL(expectedOutput, outputChannel.read());
    }

BOOST_AUTO_TEST_SUITE_END()
