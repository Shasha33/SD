#include <boost/test/unit_test.hpp>
#include <channels/StringChannel.h>

#include <iostream>

BOOST_AUTO_TEST_SUITE(StringChannelSuite)

    BOOST_AUTO_TEST_CASE(testEmpty) {
        StringChannel stringChannel;

        BOOST_CHECK_EQUAL(true, stringChannel.empty());

        stringChannel.write('a');

        BOOST_CHECK_EQUAL(false, stringChannel.empty());
        stringChannel.read();
        BOOST_CHECK_EQUAL(true, stringChannel.empty());

        stringChannel.write("abc");
        stringChannel.write('x');
        BOOST_CHECK_EQUAL(false, stringChannel.empty());
        stringChannel.read();
        BOOST_CHECK_EQUAL(true, stringChannel.empty());

        stringChannel.write('x');
        stringChannel.write("abc");
        BOOST_CHECK_EQUAL(false, stringChannel.empty());
        stringChannel.read();
        BOOST_CHECK_EQUAL(true, stringChannel.empty());

        stringChannel.write("krej rekjg rekjn");
        BOOST_CHECK_EQUAL(false, stringChannel.empty());
        stringChannel.write("");
        BOOST_CHECK_EQUAL(false, stringChannel.empty());

        stringChannel.clear();
        BOOST_CHECK_EQUAL(true, stringChannel.empty());
        stringChannel.write("");
        BOOST_CHECK_EQUAL(true, stringChannel.empty());
    }

    BOOST_AUTO_TEST_CASE(testClear) {
        StringChannel stringChannel;

        stringChannel.clear();
        BOOST_CHECK_EQUAL(true, stringChannel.empty());

        stringChannel.write('x');
        BOOST_CHECK_EQUAL(false, stringChannel.empty());

        stringChannel.write("string");
        BOOST_CHECK_EQUAL(false, stringChannel.empty());

        stringChannel.clear();
        BOOST_CHECK_EQUAL(true, stringChannel.empty());

        stringChannel.write(std::string(10000, 'x'));
        for (size_t i = 0; i < 10000; i++) {
            stringChannel.write(char(i % 26 + 'a'));
        }
        BOOST_CHECK_EQUAL(false, stringChannel.empty());
        stringChannel.clear();
        BOOST_CHECK_EQUAL(true, stringChannel.empty());
    }

    BOOST_AUTO_TEST_CASE(testRead) {
        StringChannel stringChannel;

        BOOST_CHECK_EQUAL("", stringChannel.read());

        stringChannel.write('x');
        BOOST_CHECK_EQUAL("x", stringChannel.read());
        BOOST_CHECK_EQUAL("", stringChannel.read());

        stringChannel.write('x');
        stringChannel.write('x');
        stringChannel.write('x');
        BOOST_CHECK_EQUAL("xxx", stringChannel.read());
        BOOST_CHECK_EQUAL("", stringChannel.read());

        stringChannel.write("first long part  \t");
        stringChannel.write('=');
        stringChannel.write("second long part   ");

        BOOST_CHECK_EQUAL("first long part  \t=second long part   ", stringChannel.read());
        BOOST_CHECK_EQUAL("", stringChannel.read());
    }

    BOOST_AUTO_TEST_CASE(testWriteChar) {
        StringChannel stringChannel;

        stringChannel.write('x');
        BOOST_CHECK_EQUAL("x", stringChannel.read());

        stringChannel.write('x');
        stringChannel.write('y');
        BOOST_CHECK_EQUAL("xy", stringChannel.read());

        stringChannel.write('x');
        stringChannel.write('y');
        stringChannel.write("_abc_");
        stringChannel.write('t');
        BOOST_CHECK_EQUAL("xy_abc_t", stringChannel.read());

        std::string buffer;

        for (int i = 0; i < 1000; i++) {
            char c = char(i % 26 + 'a');
            buffer.push_back(c);
            stringChannel.write(c);
        }

        BOOST_CHECK_EQUAL(buffer, stringChannel.read());
        BOOST_CHECK_EQUAL("", stringChannel.read());
        BOOST_CHECK_EQUAL(true, stringChannel.empty());
    }

    BOOST_AUTO_TEST_CASE(testWriteStrng) {
        StringChannel stringChannel;

        std::string buffer;

        for (int i = 0; i < 100; i++) {
            int l = i % 10 + 2;
            std::string subBuffer;
            for (int j = 0; j < l; j++) {
                char c = (i * 228 + j) % 26;
                subBuffer.push_back(c);
            }
            buffer += subBuffer;
            stringChannel.write(subBuffer);
        }

        BOOST_CHECK_EQUAL(buffer, stringChannel.read());
        BOOST_CHECK_EQUAL("", stringChannel.read());
        BOOST_CHECK_EQUAL(true, stringChannel.empty());
    }

BOOST_AUTO_TEST_SUITE_END()
