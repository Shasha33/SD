#include <executors/grep/GrepExecutor.h>
#include <executors/grep/GrepArguments.h>
#include <fstream>
#include <regex>
#include <iostream>

Status GrepExecutor::execute(
        const Command &command,
        StringChannel &inputChannel,
        StringChannel &outputChannel
) const {

    GrepArguments arguments = GrepArguments(command);

    if (!arguments.getFiles().empty()) {
        inputChannel.clear();
        for (const std::string &fileName : arguments.getFiles()) {
            inputChannel.writeFile(fileName);
        }
    }

    return executeFromChannelMode(inputChannel, outputChannel, arguments);
}

Status GrepExecutor::executeFromChannelMode(
        StringChannel &inputChannel,
        StringChannel &outputChannel,
        const GrepArguments &arguments
) const {

    std::regex regex(arguments.getRegexp(), std::regex_constants::grep);
    if (arguments.isCaseInsensitivity()) {
        regex.assign(
                arguments.getRegexp(),
                std::regex_constants::grep | std::regex_constants::icase
        );
    }

    std::smatch smatch;
    size_t linesToPrint = 0u;
    while (!inputChannel.empty()) {
        std::string line = inputChannel.readLine();

        bool isMatched = false;

        if (arguments.isSearchOnlyWords()) {
            for (std::string walker = line;
                 std::regex_search(walker, smatch, wordRegex);
                 walker = smatch.suffix().str()) {
                for (const auto &token : smatch) {
                    if (std::regex_match(token.str(), regex)) {
                        isMatched = true;
                        break;
                    }
                }
            }
        } else {
            isMatched = std::regex_search(line, regex);
        }

        if (isMatched) {
            outputChannel.write(line);
            linesToPrint = arguments.getLinesNumberToPrint();
        } else if (linesToPrint > 0u) {
            outputChannel.write(line);
            linesToPrint--;
        }
    }

    return Status();
}
