#ifndef HW01_CLI_WCEXECUTOR_H
#define HW01_CLI_WCEXECUTOR_H

#include <executors/ICommandExecutor.h>
#include <optional>

// Implementation of wc command
class WCExecutor : public ICommandExecutor {
public:
    // There are two modes.
    // If arguments list is empty then
    // wc will read data from input channel.
    // Otherwise it will read data from files
    // which names are arguments of wc.
    // Then wc will output the number of
    // newlines, words and bytes in data.
    // A word is a non-zero-length sequence
    // of characters delimited by white space.
    // Newline calculates as the number of
    // newline characters in data.
    // In mode when wc reads data from files
    // it will write info about each file in
    // arguments list, also it will writes the name
    // of file near the info, and at the very end
    // total info about all files will be written
    // into output channel.
    Status execute(
            const Command &command,
            StringChannel &inputStream,
            StringChannel &outputStream
    ) const override;

private:
    class Counter;

    void writeCounterToChannel(
            const Counter &counter,
            StringChannel &outputChannel,
            const std::string &message = ""
    ) const;

    WCExecutor::Counter executeChannelMode(
            const CommandArguments &commandArguments,
            StringChannel &inputChannel,
            StringChannel &outputChannel
    ) const;

    WCExecutor::Counter executeFileMode(const std::string &fileName) const;

    class Counter {
    public:
        void append(char c);

        void append(const std::string &s);

        int getNewlinesCount() const;

        int getWordsCount() const;

        int getBytesCount() const;

        void append(const Counter &other);

    private:
        static bool isWordSymbol(char c);

    private:
        int newlinesCount = 0;
        int wordsCount = 0;
        int bytesCount = 0;

        std::optional<char> lastSymbol;
    };
};


#endif //HW01_CLI_WCEXECUTOR_H
