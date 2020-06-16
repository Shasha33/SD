#include <boost/test/unit_test.hpp>
#include <executors/ExitExecutor.h>
#include <channels/StringChannel.h>

BOOST_AUTO_TEST_SUITE(ExitExecutorSuite)

    BOOST_AUTO_TEST_CASE(testExecuteEmptyArguments) {
        Command command = Command(CommandName("exit"), CommandArguments());
        StringChannel inputChannel, outputChannel;
        Status status = ExitExecutor().execute(command, inputChannel, outputChannel);
        BOOST_CHECK_EQUAL(true, outputChannel.empty());
        BOOST_CHECK_EQUAL(0, status.getExitCode());
        BOOST_CHECK_EQUAL(ExitStatus::EXIT, status.getExitStatus());
    }

    BOOST_AUTO_TEST_CASE(testExecuteOneArgument) {
        Command command = Command(
                CommandName("exit"),
                CommandArguments(
                        {
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "123")
                        }
                )
        );
        StringChannel inputChannel, outputChannel;
        Status status = ExitExecutor().execute(command, inputChannel, outputChannel);
        BOOST_CHECK_EQUAL(true, outputChannel.empty());
        BOOST_CHECK_EQUAL(123, status.getExitCode());
        BOOST_CHECK_EQUAL(ExitStatus::EXIT, status.getExitStatus());
    }

    BOOST_AUTO_TEST_CASE(testExecuteTooManyArguments) {
        Command command = Command(
                CommandName("exit"),
                CommandArguments(
                        {
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "123"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::DOLLAR, "$"),
                        }
                )
        );
        StringChannel inputChannel, outputChannel;
        BOOST_CHECK_THROW(
                ExitExecutor().execute(command, inputChannel, outputChannel),
                std::invalid_argument
        );
    }

    BOOST_AUTO_TEST_CASE(testExecuteInvalidExitCode) {
        Command command = Command(
                CommandName("exit"),
                CommandArguments(
                        {
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "xyz123abc"),
                        }
                )
        );
        StringChannel inputChannel, outputChannel;
        BOOST_CHECK_THROW(
                ExitExecutor().execute(command, inputChannel, outputChannel),
                std::invalid_argument
        );
    }


BOOST_AUTO_TEST_SUITE_END()
