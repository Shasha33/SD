#include <boost/test/unit_test.hpp>
#include <commands/CommandName.h>

BOOST_AUTO_TEST_SUITE(CommandNameSuite)

    BOOST_AUTO_TEST_CASE(testGetNameEmptyName) {
        BOOST_CHECK_EQUAL("", CommandName("").getName());
    }

    BOOST_AUTO_TEST_CASE(testGetName) {
        BOOST_CHECK_EQUAL(
                "\"qwertyuiop[]asdfghjkl;'zxcvbnm,./!@#$%^&*()_+1234567890-=\"",
                CommandName("\"qwertyuiop[]asdfghjkl;'zxcvbnm,./!@#$%^&*()_+1234567890-=\"").getName()
        );
    }

    BOOST_AUTO_TEST_CASE(testEqual2EmptyNames) {
        BOOST_CHECK_EQUAL(true, CommandName("") == CommandName(""));
    }

    BOOST_AUTO_TEST_CASE(testEqualEmptyNameVsNonEmptyName) {
        BOOST_CHECK_EQUAL(false, CommandName("") == CommandName("abc"));
        BOOST_CHECK_EQUAL(false, CommandName("abc") == CommandName(""));
    }

    BOOST_AUTO_TEST_CASE(testEqual2NonEmptyNames) {
        std::string name = "\"qwertyuiop[]asdfghjkl;'zxcvbnm,./!@#$%^&*()_+1234567890-=\"";
        BOOST_CHECK_EQUAL(false, CommandName("abc") == CommandName("xyz"));
        BOOST_CHECK_EQUAL(true, CommandName(name) == CommandName(name));
    }

BOOST_AUTO_TEST_SUITE_END()
