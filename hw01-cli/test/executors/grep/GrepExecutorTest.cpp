#include <boost/test/unit_test.hpp>
#include <executors/grep/GrepExecutor.h>

BOOST_AUTO_TEST_SUITE(GrepExecutorSuite)

    BOOST_AUTO_TEST_CASE(testGrepWithoutFlag) {
        GrepExecutor grepExecutor;
        StringChannel inputChannel, outputChannel;
        Command command = Command(
                CommandName("grep"),
                CommandArguments(
                        {
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "xyz"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "resources/grep_file.txt")
                        }
                )
        );

        Status status = grepExecutor.execute(command, inputChannel, outputChannel);
        std::string expectedOutput = "abc,def, xyzcccc123\n"
                                     "abc xyz 123\n"
                                     "xyz\n"
                                     "123,xyz,456 hah\n";

        BOOST_CHECK_EQUAL(expectedOutput, outputChannel.read());
    }

    BOOST_AUTO_TEST_CASE(testCaseSensitivityFlag) {
        GrepExecutor grepExecutor;
        StringChannel inputChannel, outputChannel;
        Command command = Command(
                CommandName("grep"),
                CommandArguments(
                        {
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "-i"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "xyz"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "resources/grep_file.txt")
                        }
                )
        );

        Status status = grepExecutor.execute(command, inputChannel, outputChannel);
        std::string expectedOutput = "abc,def, xyzcccc123\n"
                                     "abc xyz 123\n"
                                     "aBc XYz 123\n"
                                     "xyz\n"
                                     "123,xyz,456 hah\n";

        BOOST_CHECK_EQUAL(expectedOutput, outputChannel.read());
    }

    BOOST_AUTO_TEST_CASE(testWordsOnlyFlag) {
        GrepExecutor grepExecutor;
        StringChannel inputChannel, outputChannel;
        Command command = Command(
                CommandName("grep"),
                CommandArguments(
                        {
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "-w"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "xyz"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "resources/grep_file.txt")
                        }
                )
        );

        Status status = grepExecutor.execute(command, inputChannel, outputChannel);
        std::string expectedOutput = "abc xyz 123\n"
                                     "xyz\n"
                                     "123,xyz,456 hah\n";

        BOOST_CHECK_EQUAL(expectedOutput, outputChannel.read());
    }

    BOOST_AUTO_TEST_CASE(testNlinesToPrintFlag) {
        GrepExecutor grepExecutor;
        StringChannel inputChannel, outputChannel;
        Command command = Command(
                CommandName("grep"),
                CommandArguments(
                        {
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "-A"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "1"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "xyz"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "resources/grep_file.txt")
                        }
                )
        );

        Status status = grepExecutor.execute(command, inputChannel, outputChannel);
        std::string expectedOutput = "abc,def, xyzcccc123\n"
                                     "abc xyz 123\n"
                                     "aBc XYz 123\n"
                                     "xyz\n"
                                     "12xy z\n"
                                     "123,xyz,456 hah\n";

        BOOST_CHECK_EQUAL(expectedOutput, outputChannel.read());
    }

    BOOST_AUTO_TEST_CASE(testMultipleFlags) {
        GrepExecutor grepExecutor;
        StringChannel inputChannel, outputChannel;
        Command command = Command(
                CommandName("grep"),
                CommandArguments(
                        {
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "-wi"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "xyz"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "resources/grep_file.txt")
                        }
                )
        );

        Status status = grepExecutor.execute(command, inputChannel, outputChannel);
        std::string expectedOutput = "abc xyz 123\n"
                                     "aBc XYz 123\n"
                                     "xyz\n"
                                     "123,xyz,456 hah\n";

        BOOST_CHECK_EQUAL(expectedOutput, outputChannel.read());
    }

    BOOST_AUTO_TEST_CASE(testIncorrectFlagValue) {
        GrepExecutor grepExecutor;
        StringChannel inputChannel, outputChannel;
        Command command = Command(
                CommandName("grep"),
                CommandArguments(
                        {
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "-A"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "-10"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "xyz"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "resources/grep_file.txt")
                        }
                )
        );

        BOOST_CHECK_THROW(
                grepExecutor.execute(command, inputChannel, outputChannel),
                std::exception
        );
    }

    BOOST_AUTO_TEST_CASE(testGrepWithoutFlagInputChannel) {
        GrepExecutor grepExecutor;
        StringChannel inputChannel, outputChannel;
        Command command = Command(
                CommandName("grep"),
                CommandArguments(
                        {
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "xyz")
                        }
                )
        );

        inputChannel.writeFile("resources/grep_file.txt");

        Status status = grepExecutor.execute(command, inputChannel, outputChannel);
        std::string expectedOutput = "abc,def, xyzcccc123\n"
                                     "abc xyz 123\n"
                                     "xyz\n"
                                     "123,xyz,456 hah\n";

        BOOST_CHECK_EQUAL(expectedOutput, outputChannel.read());
    }

    BOOST_AUTO_TEST_CASE(testCaseSensitivityFlagInputChannel) {
        GrepExecutor grepExecutor;
        StringChannel inputChannel, outputChannel;
        Command command = Command(
                CommandName("grep"),
                CommandArguments(
                        {
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "-i"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "xyz")
                        }
                )
        );

        inputChannel.writeFile("resources/grep_file.txt");

        Status status = grepExecutor.execute(command, inputChannel, outputChannel);
        std::string expectedOutput = "abc,def, xyzcccc123\n"
                                     "abc xyz 123\n"
                                     "aBc XYz 123\n"
                                     "xyz\n"
                                     "123,xyz,456 hah\n";

        BOOST_CHECK_EQUAL(expectedOutput, outputChannel.read());
    }

    BOOST_AUTO_TEST_CASE(testWordsOnlyFlagInputChannel) {
        GrepExecutor grepExecutor;
        StringChannel inputChannel, outputChannel;
        Command command = Command(
                CommandName("grep"),
                CommandArguments(
                        {
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "-w"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "xyz")
                        }
                )
        );

        inputChannel.writeFile("resources/grep_file.txt");

        Status status = grepExecutor.execute(command, inputChannel, outputChannel);
        std::string expectedOutput = "abc xyz 123\n"
                                     "xyz\n"
                                     "123,xyz,456 hah\n";

        BOOST_CHECK_EQUAL(expectedOutput, outputChannel.read());
    }

    BOOST_AUTO_TEST_CASE(testNlinesToPrintFlagInputChannel) {
        GrepExecutor grepExecutor;
        StringChannel inputChannel, outputChannel;
        Command command = Command(
                CommandName("grep"),
                CommandArguments(
                        {
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "-A"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "1"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "xyz")
                        }
                )
        );

        inputChannel.writeFile("resources/grep_file.txt");

        Status status = grepExecutor.execute(command, inputChannel, outputChannel);
        std::string expectedOutput = "abc,def, xyzcccc123\n"
                                     "abc xyz 123\n"
                                     "aBc XYz 123\n"
                                     "xyz\n"
                                     "12xy z\n"
                                     "123,xyz,456 hah\n";

        BOOST_CHECK_EQUAL(expectedOutput, outputChannel.read());
    }

    BOOST_AUTO_TEST_CASE(testMultipleFlagsInputChannel) {
        GrepExecutor grepExecutor;
        StringChannel inputChannel, outputChannel;
        Command command = Command(
                CommandName("grep"),
                CommandArguments(
                        {
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "-wi"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "xyz")
                        }
                )
        );

        inputChannel.writeFile("resources/grep_file.txt");

        Status status = grepExecutor.execute(command, inputChannel, outputChannel);
        std::string expectedOutput = "abc xyz 123\n"
                                     "aBc XYz 123\n"
                                     "xyz\n"
                                     "123,xyz,456 hah\n";

        BOOST_CHECK_EQUAL(expectedOutput, outputChannel.read());
    }

    BOOST_AUTO_TEST_CASE(testIncorrectFlagValueInputChannel) {
        GrepExecutor grepExecutor;
        StringChannel inputChannel, outputChannel;
        Command command = Command(
                CommandName("grep"),
                CommandArguments(
                        {
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "-A"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "-10"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "xyz")
                        }
                )
        );

        inputChannel.writeFile("resources/grep_file.txt");

        BOOST_CHECK_THROW(
                grepExecutor.execute(command, inputChannel, outputChannel),
                std::exception
        );
    }

BOOST_AUTO_TEST_SUITE_END()
