#include <boost/test/unit_test.hpp>
#include <executors/EchoExecutor.h>
#include <channels/StringChannel.h>

BOOST_AUTO_TEST_SUITE(EchoExecutorSuite)

    BOOST_AUTO_TEST_CASE(testExecuteEmptyArguments) {
        StringChannel inputChannel, outputChannel;
        Command command = Command(
                CommandName("echo"),
                CommandArguments(
                        {
                                Token(TokenType::END)
                        }
                )
        );
        Status status = EchoExecutor().execute(command, inputChannel, outputChannel);
        BOOST_CHECK_EQUAL(true, status.isSuccess());
        BOOST_CHECK_EQUAL("\n", outputChannel.read());
    }

    BOOST_AUTO_TEST_CASE(testExecuteNonEmptyArguments) {
        StringChannel inputChannel, outputChannel;
        Command command = Command(
                CommandName("echo"),
                CommandArguments(
                        {
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "a"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::DOLLAR, "$"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "b"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::END)
                        }
                )
        );
        Status status = EchoExecutor().execute(command, inputChannel, outputChannel);
        BOOST_CHECK_EQUAL(true, status.isSuccess());
        BOOST_CHECK_EQUAL("a $ b\n", outputChannel.read());
    }

BOOST_AUTO_TEST_SUITE_END()
