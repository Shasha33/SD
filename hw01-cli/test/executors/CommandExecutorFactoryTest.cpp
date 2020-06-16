#include <boost/test/unit_test.hpp>
#include <commands/CommandExecutorFactory.h>
#include <executors/ICommandExecutor.h>
#include <channels/StringChannel.h>


BOOST_AUTO_TEST_SUITE(CommandExecutorFactorySuite)

    BOOST_AUTO_TEST_CASE(testRegister) {

        class ForTestExecutor : public ICommandExecutor {
        public:
            ForTestExecutor(char type) : type(type) {}

            Status execute(
                    const Command &command,
                    StringChannel &inputChannel,
                    StringChannel &outputChannel
            ) const override {
                outputChannel.write(type);
                return Status();
            }

        private:
            char type;
        };

        StringChannel inputChannel, outputChannel;

        CommandExecutorFactory factory;
        std::unique_ptr<ICommandExecutor> aExecutor(new ForTestExecutor('a'));
        std::unique_ptr<ICommandExecutor> bExecutor(new ForTestExecutor('b'));
        std::unique_ptr<ICommandExecutor> cExecutor(new ForTestExecutor('c'));

        factory.registerExecutor(CommandName("a"), aExecutor.get());
        factory.registerExecutor(CommandName("b"), bExecutor.get());
        factory.registerExecutor(CommandName("c"), cExecutor.get());

        outputChannel.clear();
        factory.getCommandExecutorByCommandName(CommandName("a"))
                .value()->execute(Command(), inputChannel, outputChannel);
        BOOST_CHECK_EQUAL("a", outputChannel.read());

        outputChannel.clear();
        factory.getCommandExecutorByCommandName(CommandName("b"))
                .value()->execute(Command(), inputChannel, outputChannel);
        BOOST_CHECK_EQUAL("b", outputChannel.read());

        outputChannel.clear();
        factory.getCommandExecutorByCommandName(CommandName("c"))
                .value()->execute(Command(), inputChannel, outputChannel);
        BOOST_CHECK_EQUAL("c", outputChannel.read());

        outputChannel.clear();
        BOOST_CHECK_EQUAL(
                false,
                factory.getCommandExecutorByCommandName(CommandName("d")).has_value()
        );
    }

BOOST_AUTO_TEST_SUITE_END()
