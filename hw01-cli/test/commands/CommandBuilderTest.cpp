#include <boost/test/unit_test.hpp>
#include <commands/CommandBuilder.h>

BOOST_AUTO_TEST_SUITE(CommandBuilderSuite)

    BOOST_AUTO_TEST_CASE(testClear) {
        CommandBuilder builder;

        for (int i = 0; i < 10; i++) {
            builder.appendToken(Token(TokenType::LITERAL, std::to_string(i)));
        }

        BOOST_CHECK_EQUAL(false, builder.buildCommandString().empty());
        BOOST_CHECK_EQUAL(false, builder.buildCommandString().empty());

        builder.clear();

        BOOST_CHECK_EQUAL(true, builder.buildCommandString().empty());
        BOOST_CHECK_EQUAL(true, builder.buildCommandString().empty());

        builder.clear();
        builder.clear();

        BOOST_CHECK_EQUAL(true, builder.buildCommandString().empty());
        BOOST_CHECK_EQUAL(true, builder.buildCommandString().empty());
    }

    BOOST_AUTO_TEST_CASE(testBuildCommandString) {
        CommandBuilder builder;
        std::string buffer;

        for (int i = 0; i < 10; i++) {
            std::string helper = std::to_string(i);
            builder.appendToken(Token(TokenType::LITERAL, helper));
            buffer += helper;
        }

        BOOST_CHECK_EQUAL(buffer, builder.buildCommandString());
    }

    BOOST_AUTO_TEST_CASE(testBuildCommandStringAppendNonLiteralAndEmptyTokens) {
        CommandBuilder builder;
        std::string buffer;

        std::vector<TokenType> types = {
                PIPE, DOLLAR, ASSIGN, END, SPACE, LITERAL
        };

        for (int i = 0; i < 20; i++) {
            TokenType type = types[i % (int) types.size()];
            std::string content = std::to_string(i);
            if (type == TokenType::LITERAL) {
                content.clear();
            }
            Token token = Token(type, content);
            builder.appendToken(token);
        }

        BOOST_CHECK_EQUAL("", builder.buildCommandString());
    }

    BOOST_AUTO_TEST_CASE(testBuildCommandStringWithAppendNonLiteralTokenAtStart) {
        CommandBuilder builder;
        std::string buffer;

        builder.appendToken(Token(TokenType::SPACE, " "));
        builder.appendToken(Token(TokenType::DOLLAR, "$"));
        builder.appendToken(Token(TokenType::LITERAL, "echo"));
        builder.appendToken(Token(TokenType::SPACE, " "));
        builder.appendToken(Token(TokenType::LITERAL, "x"));
        builder.appendToken(Token(TokenType::SPACE, " "));
        builder.appendToken(Token(TokenType::LITERAL, "y"));
        builder.appendToken(Token(TokenType::SPACE, " "));
        builder.appendToken(Token(TokenType::SPACE, " "));
        builder.appendToken(Token(TokenType::LITERAL, "z"));

        BOOST_CHECK_EQUAL("echo x y  z", builder.buildCommandString());
    }

    BOOST_AUTO_TEST_CASE(testAppend) {
        CommandBuilder builder;

        builder.appendToken(Token(TokenType::SPACE, " "));
        BOOST_CHECK_EQUAL("", builder.buildCommandString());
        builder.clear();

        builder.appendToken(Token(TokenType::LITERAL, "echo"));
        builder.appendToken(Token(TokenType::SPACE, " "));
        builder.appendToken(Token(TokenType::ASSIGN, "="));
        BOOST_CHECK_EQUAL("echo =", builder.buildCommandString());
        builder.clear();
    }

    BOOST_AUTO_TEST_CASE(testBuildCommand) {
        CommandBuilder builder;
        std::string buffer;

        builder.appendToken(Token(TokenType::SPACE, " "));
        builder.appendToken(Token(TokenType::DOLLAR, "$"));
        builder.appendToken(Token(TokenType::LITERAL, "cat"));
        builder.appendToken(Token(TokenType::SPACE, " "));
        builder.appendToken(Token(TokenType::LITERAL, "x"));
        builder.appendToken(Token(TokenType::PIPE, "|"));
        builder.appendToken(Token(TokenType::SPACE, " "));
        builder.appendToken(Token(TokenType::LITERAL, "wc"));
        builder.appendToken(Token(TokenType::SPACE, " "));
        builder.appendToken(Token(TokenType::PIPE, "|"));
        builder.appendToken(Token(TokenType::SPACE, " "));
        builder.appendToken(Token(TokenType::LITERAL, "sort"));

        Command command = builder.buildCommand();

        BOOST_CHECK_EQUAL("cat", command.getCommandName().getName());
        BOOST_CHECK_EQUAL(" x| wc | sort", command.getCommandArguments().asString());
    }

    BOOST_AUTO_TEST_CASE(testBuildCommandEmptyCommand) {
        CommandBuilder builder;
        std::string buffer;

        builder.appendToken(Token(TokenType::SPACE, " "));
        builder.appendToken(Token(TokenType::DOLLAR, "$"));
        builder.appendToken(Token(TokenType::PIPE, "|"));
        builder.appendToken(Token(TokenType::ASSIGN, "="));
        builder.appendToken(Token(TokenType::END, ""));

        Command command = builder.buildCommand();

        BOOST_CHECK_EQUAL("", command.getCommandName().getName());
        BOOST_CHECK_EQUAL("", command.getCommandArguments().asString());
    }

BOOST_AUTO_TEST_SUITE_END()
