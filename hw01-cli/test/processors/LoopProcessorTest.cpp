#include <boost/test/unit_test.hpp>
#include <processors/LoopProcessor.h>
#include <channels/StringChannel.h>

#include <iostream>

BOOST_AUTO_TEST_SUITE(LoopProcessorSuite)

    BOOST_AUTO_TEST_CASE(testCase1) {
        LoopProcessor processor;
        Environment environment;
        FileTreeState fileTreeState;

        std::string command = "cat resources/wc_test_file.txt resources/wc_test_file2.txt | wc";

        Response response = processor.process(command, environment, fileTreeState);
        StringChannel outputChannel = response.getStringChannel();

        BOOST_CHECK_EQUAL(true, response.getStatus().isSuccess());
        BOOST_CHECK_EQUAL("21 43 137\n", outputChannel.read());
    }

    BOOST_AUTO_TEST_CASE(testCase2) {
        LoopProcessor processor;
        Environment environment;
        FileTreeState fileTreeState;

        std::string command = "     echo \"1  xxy  2\"       '       '";

        Response response = processor.process(command, environment, fileTreeState);
        StringChannel outputChannel = response.getStringChannel();

        BOOST_CHECK_EQUAL(true, response.getStatus().isSuccess());
        BOOST_CHECK_EQUAL("1 xxy 2\n", outputChannel.read());
    }

    BOOST_AUTO_TEST_CASE(testCase3) {
        LoopProcessor processor;
        Environment environment;
        FileTreeState fileTreeState;

        std::string command;

        Response response = processor.process(command, environment, fileTreeState);
        StringChannel outputChannel = response.getStringChannel();

        BOOST_CHECK_EQUAL(true, response.getStatus().isSuccess());
        BOOST_CHECK_EQUAL("", outputChannel.read());
    }

BOOST_AUTO_TEST_SUITE_END()
