#include <executors/WCExecutor.h>
#include <fstream>

Status WCExecutor::execute(
        const Command &command,
        StringChannel &inputStream,
        StringChannel &outputStream
) const {
    const CommandArguments &commandArguments = command.getCommandArguments();
    if (commandArguments.countTokensWithType(TokenType::LITERAL) > 0) {
        Counter totalCounter;
        for (const auto &token : commandArguments.asTokensVector()) {
            if (token.getTokenType() != TokenType::LITERAL) {
                continue;
            }
            const std::string &fileName = token.asString();
            Counter counter = executeFileMode(fileName);
            writeCounterToChannel(counter, outputStream, fileName);
            totalCounter.append(counter);
        }
        writeCounterToChannel(totalCounter, outputStream, "total");
    } else {
        Counter counter = executeChannelMode(commandArguments, inputStream, outputStream);
        writeCounterToChannel(counter, outputStream);
    }
    return Status();
}

WCExecutor::Counter WCExecutor::executeChannelMode(
        const CommandArguments &commandArguments,
        StringChannel &inputChannel,
        StringChannel &outputChannel
) const {
    Counter counter;
    while (!inputChannel.empty()) {
        counter.append(inputChannel.read());
    }
    return counter;
}

WCExecutor::Counter WCExecutor::executeFileMode(
        const std::string &fileName
) const {
    std::ifstream fin(fileName);
    Counter counter;
    for (char c; fin.get(c);) {
        counter.append(c);
    }
    return counter;
}

void WCExecutor::writeCounterToChannel(
        const WCExecutor::Counter &counter,
        StringChannel &outputChannel,
        const std::string &message
) const {
    outputChannel.write(std::to_string(counter.getNewlinesCount()) + " ");
    outputChannel.write(std::to_string(counter.getWordsCount()) + " ");
    outputChannel.write(std::to_string(counter.getBytesCount()));
    if (!message.empty()) {
        outputChannel.write(" " + message);
    }
    outputChannel.write("\n");
}


int WCExecutor::Counter::getNewlinesCount() const {
    return newlinesCount;
}

int WCExecutor::Counter::getWordsCount() const {
    return wordsCount;
}

int WCExecutor::Counter::getBytesCount() const {
    return bytesCount;
}

void WCExecutor::Counter::append(char c) {
    bytesCount++;
    if (c == '\n') {
        newlinesCount++;
    }
    if ((!lastSymbol.has_value() || !isWordSymbol(lastSymbol.value())) && isWordSymbol(c)) {
        wordsCount++;
    }
    lastSymbol = c;
}

bool WCExecutor::Counter::isWordSymbol(char c) {
    return !std::isspace(c);
}

void WCExecutor::Counter::append(const std::string &s) {
    for (char c : s) {
        append(c);
    }
}

void WCExecutor::Counter::append(const WCExecutor::Counter &other) {
    newlinesCount += other.newlinesCount;
    wordsCount += other.wordsCount;
    bytesCount += other.bytesCount;
}


