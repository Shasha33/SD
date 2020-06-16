#include <boost/test/unit_test.hpp>
#include <commands/Command.h>

BOOST_AUTO_TEST_SUITE(CommandSuite)

    BOOST_AUTO_TEST_CASE(testAsStringEmptyCommand) {
        Command command = Command(CommandName(""), CommandArguments());
        BOOST_CHECK_EQUAL("", command.asString());
    }

    BOOST_AUTO_TEST_CASE(testAsStringEmptyArguments) {
        Command command = Command(CommandName("cmd"), CommandArguments());
        BOOST_CHECK_EQUAL("cmd", command.asString());
    }

    BOOST_AUTO_TEST_CASE(testAsStringEmptyName) {
        Command command = Command(
                CommandName(""),
                CommandArguments(
                        {
                                Token(TokenType::LITERAL, "arg1"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::DOLLAR, "$"),
                                Token(TokenType::LITERAL, "var")
                        }
                )
        );
        BOOST_CHECK_EQUAL("arg1 $var", command.asString());
    }

    BOOST_AUTO_TEST_CASE(testAsString) {
        Command command = Command(
                CommandName("echo"),
                CommandArguments(
                        {
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "arg1"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::DOLLAR, "$"),
                                Token(TokenType::LITERAL, "var")
                        }
                )
        );
        BOOST_CHECK_EQUAL("echo arg1 $var", command.asString());
    }

BOOST_AUTO_TEST_SUITE_END()
