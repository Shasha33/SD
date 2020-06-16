#include <boost/test/unit_test.hpp>
#include <Substitutor.h>

BOOST_AUTO_TEST_SUITE(SubstitutorSuite)

    BOOST_AUTO_TEST_CASE(testTryAssignReturnValue) {
        Environment environment;

        Command command = Command(
                CommandName("!@##@%%@$5"),
                CommandArguments(
                        {
                                Token(TokenType::ASSIGN, "="),
                                Token(TokenType::LITERAL, "value")
                        }
                )
        );

        BOOST_CHECK_EQUAL(false, Substitutor::tryAssign(command, environment));

        command = Command(
                CommandName("name"),
                CommandArguments(
                        {
                                Token(TokenType::ASSIGN, "="),
                                Token(TokenType::LITERAL, "value")
                        }
                )
        );

        BOOST_CHECK_EQUAL(true, Substitutor::tryAssign(command, environment));

        command = Command(
                CommandName("!@##@%%@$5"),
                CommandArguments(
                        {
                                Token(TokenType::ASSIGN, "="),
                                Token(TokenType::LITERAL, "value"),
                                Token(TokenType::LITERAL, "oneMore"),
                        }
                )
        );

        BOOST_CHECK_EQUAL(false, Substitutor::tryAssign(command, environment));

        command = Command(
                CommandName("!@##@%%@$5"),
                CommandArguments(
                        {
                                Token(TokenType::ASSIGN, "=")
                        }
                )
        );

        BOOST_CHECK_EQUAL(false, Substitutor::tryAssign(command, environment));
    }

    BOOST_AUTO_TEST_CASE(testTryAssignEffect) {
        Environment environment;

        Command command = Command(
                CommandName("aZ193"),
                CommandArguments(
                        {
                                Token(TokenType::ASSIGN, "="),
                                Token(TokenType::LITERAL, "value")
                        }
                )
        );

        BOOST_CHECK_EQUAL(true, Substitutor::tryAssign(command, environment));

        BOOST_CHECK_EQUAL("value", environment.getVariableValue("aZ193"));
        BOOST_CHECK_EQUAL("", environment.getVariableValue("aZ193suff"));
    }

    BOOST_AUTO_TEST_CASE(testSubstitute) {
        Token token = Token(TokenType::END);
        Environment environment;

        token = Token(TokenType::END, "\"$x\"");
        token = Substitutor::substitute(token, environment);
        BOOST_CHECK_EQUAL("\"$x\"", token.asString());

        token = Token(TokenType::PIPE, "\"$x\"");
        token = Substitutor::substitute(token, environment);
        BOOST_CHECK_EQUAL("\"$x\"", token.asString());

        token = Token(TokenType::ASSIGN, "\"$x\"");
        token = Substitutor::substitute(token, environment);
        BOOST_CHECK_EQUAL("\"$x\"", token.asString());

        token = Token(TokenType::DOLLAR, "\"$x\"");
        token = Substitutor::substitute(token, environment);
        BOOST_CHECK_EQUAL("\"$x\"", token.asString());

        token = Token(TokenType::SPACE, "\"$x\"");
        token = Substitutor::substitute(token, environment);
        BOOST_CHECK_EQUAL("\"$x\"", token.asString());

        token = Token(TokenType::LITERAL, "\"$x\"");
        token = Substitutor::substitute(token, environment);
        BOOST_CHECK_EQUAL("\"\"", token.asString());
    }

BOOST_AUTO_TEST_SUITE_END()
