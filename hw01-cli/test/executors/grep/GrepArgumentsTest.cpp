#include <boost/test/unit_test.hpp>
#include <executors/grep/GrepArguments.h>

BOOST_AUTO_TEST_SUITE(GrepArgumentsSuite)

    BOOST_AUTO_TEST_CASE(testFlagsReadOneFileMode) {
        Command command = Command(
                CommandName("grep"),
                CommandArguments(
                        {
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "-i"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "-w"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "-A"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "100"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "regexp"),
                                Token(TokenType::SPACE, " "),
                                Token(TokenType::LITERAL, "file"),
                        }
                )
        );

        GrepArguments arguments(command);

        BOOST_CHECK_EQUAL(true, arguments.isCaseInsensitivity());
        BOOST_CHECK_EQUAL(true, arguments.isSearchOnlyWords());
        BOOST_CHECK_EQUAL(100, arguments.getLinesNumberToPrint());
        BOOST_CHECK_EQUAL("regexp", arguments.getRegexp());

        std::vector<std::string> files = {"file"};
        BOOST_CHECK_EQUAL(files.size(), arguments.getFiles().size());
        for (size_t i = 0; i < files.size(); i++) {
                BOOST_CHECK_EQUAL(files[i], arguments.getFiles()[i]);
        }
    }

    BOOST_AUTO_TEST_CASE(testFlagsReadMultipleFilesMode) {
            Command command = Command(
                    CommandName("grep"),
                    CommandArguments(
                            {
                                    Token(TokenType::SPACE, " "),
                                    Token(TokenType::LITERAL, "-i"),
                                    Token(TokenType::SPACE, " "),
                                    Token(TokenType::LITERAL, "-w"),
                                    Token(TokenType::SPACE, " "),
                                    Token(TokenType::LITERAL, "-A"),
                                    Token(TokenType::SPACE, " "),
                                    Token(TokenType::LITERAL, "100"),
                                    Token(TokenType::SPACE, " "),
                                    Token(TokenType::LITERAL, "regexp"),
                                    Token(TokenType::SPACE, " "),
                                    Token(TokenType::LITERAL, "file1"),
                                    Token(TokenType::SPACE, " "),
                                    Token(TokenType::LITERAL, "file2"),
                                    Token(TokenType::SPACE, " "),
                                    Token(TokenType::LITERAL, "file3"),
                            }
                    )
            );

            GrepArguments arguments(command);

            BOOST_CHECK_EQUAL(true, arguments.isCaseInsensitivity());
            BOOST_CHECK_EQUAL(true, arguments.isSearchOnlyWords());
            BOOST_CHECK_EQUAL(100, arguments.getLinesNumberToPrint());
            BOOST_CHECK_EQUAL("regexp", arguments.getRegexp());

            std::vector<std::string> files = {"file1", "file2", "file3"};
            BOOST_CHECK_EQUAL(files.size(), arguments.getFiles().size());
            for (size_t i = 0; i < files.size(); i++) {
                    BOOST_CHECK_EQUAL(files[i], arguments.getFiles()[i]);
            }
    }

    BOOST_AUTO_TEST_CASE(testFlagsReadNoFilesMode) {
            Command command = Command(
                    CommandName("grep"),
                    CommandArguments(
                            {
                                    Token(TokenType::SPACE, " "),
                                    Token(TokenType::LITERAL, "-i"),
                                    Token(TokenType::SPACE, " "),
                                    Token(TokenType::LITERAL, "-w"),
                                    Token(TokenType::SPACE, " "),
                                    Token(TokenType::LITERAL, "-A"),
                                    Token(TokenType::SPACE, " "),
                                    Token(TokenType::LITERAL, "100"),
                                    Token(TokenType::SPACE, " "),
                                    Token(TokenType::LITERAL, "regexp")
                            }
                    )
            );

            GrepArguments arguments(command);

            BOOST_CHECK_EQUAL(true, arguments.isCaseInsensitivity());
            BOOST_CHECK_EQUAL(true, arguments.isSearchOnlyWords());
            BOOST_CHECK_EQUAL(100, arguments.getLinesNumberToPrint());
            BOOST_CHECK_EQUAL("regexp", arguments.getRegexp());

            std::vector<std::string> files = {};
            BOOST_CHECK_EQUAL(files.size(), arguments.getFiles().size());
            for (size_t i = 0; i < files.size(); i++) {
                    BOOST_CHECK_EQUAL(files[i], arguments.getFiles()[i]);
            }
    }

    BOOST_AUTO_TEST_CASE(testNotAllFlagsReadOneFileMode) {
            Command command = Command(
                    CommandName("grep"),
                    CommandArguments(
                            {
                                    Token(TokenType::SPACE, " "),
                                    Token(TokenType::LITERAL, "-i"),
                                    Token(TokenType::SPACE, " "),
                                    Token(TokenType::LITERAL, "-w"),
                                    Token(TokenType::SPACE, " "),
                                    Token(TokenType::LITERAL, "regexp"),
                                    Token(TokenType::SPACE, " "),
                                    Token(TokenType::LITERAL, "file"),
                            }
                    )
            );

            GrepArguments arguments(command);

            BOOST_CHECK_EQUAL(true, arguments.isCaseInsensitivity());
            BOOST_CHECK_EQUAL(true, arguments.isSearchOnlyWords());
            BOOST_CHECK_EQUAL(0, arguments.getLinesNumberToPrint());
            BOOST_CHECK_EQUAL("regexp", arguments.getRegexp());

            std::vector<std::string> files = {"file"};
            BOOST_CHECK_EQUAL(files.size(), arguments.getFiles().size());
            for (size_t i = 0; i < files.size(); i++) {
                    BOOST_CHECK_EQUAL(files[i], arguments.getFiles()[i]);
            }
    }

BOOST_AUTO_TEST_SUITE_END()
