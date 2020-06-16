#include <executors/grep/GrepArguments.h>
#include <cstring>
#include <cxxopts.hpp>

GrepArguments::GrepArguments(const Command &command) {
    argv = new char *[command.getCommandArguments().size() + 1];

    argv[0] = new char[command.getCommandName().getName().size() + 1]();
    memcpy(
            argv[0],
            command.getCommandName().getName().c_str(),
            command.getCommandName().getName().size()
    );

    argc = 1;
    for (const Token &token : command.getCommandArguments().asTokensVector()) {
        if (token.getTokenType() != TokenType::LITERAL) {
            continue;
        }
        const std::string &stringArg = token.asString();
        char *arg = new char[stringArg.size() + 1]();
        memcpy(arg, stringArg.c_str(), stringArg.size());
        argv[argc++] = arg;
    }

    const std::string CASE_INSENSITIVITY_KEY = "i";
    const std::string SEARCH_ONLY_WORDS_KEY = "w";
    const std::string PRINT_N_LINES_KEY = "A";
    const std::string REGEXP_KEY = "regexp";
    const std::string FILES_KEY = "files";

    cxxopts::Options options("grep", "Prints lines matching a pattern");
    options.add_options()
            (CASE_INSENSITIVITY_KEY, "Case sensitivity")
            (SEARCH_ONLY_WORDS_KEY, "Search only whole words")
            (
                    PRINT_N_LINES_KEY,
                    "Print n lines after matched line",
                    cxxopts::value<unsigned int>()->default_value("0")
            )
            (
                    REGEXP_KEY,
                    "Regular expression to be used for search matchings",
                    cxxopts::value<std::string>()->default_value("")
            )
            (
                    FILES_KEY,
                    "File to be processed by grep",
                    cxxopts::value<std::vector<std::string>>()->default_value({})
            );
    options.parse_positional({REGEXP_KEY, FILES_KEY});
    auto result = options.parse(argc, argv);

    caseInsensitivity = result[CASE_INSENSITIVITY_KEY].as<bool>();
    searchOnlyWords = result[SEARCH_ONLY_WORDS_KEY].as<bool>();
    nLinesToPrint = result[PRINT_N_LINES_KEY].as<unsigned int>();
    regexp = result[REGEXP_KEY].as<std::string>();
    files = result[FILES_KEY].as<std::vector<std::string>>();
}

GrepArguments::~GrepArguments() {
    for (int i = 0; i < argc; i++) {
        delete[] argv[i];
    }
    delete[] argv;
}

bool GrepArguments::isCaseInsensitivity() const {
    return caseInsensitivity;
}

bool GrepArguments::isSearchOnlyWords() const {
    return searchOnlyWords;
}

unsigned int GrepArguments::getLinesNumberToPrint() const {
    return nLinesToPrint;
}

const std::string &GrepArguments::getRegexp() const {
    return regexp;
}

const std::vector<std::string> &GrepArguments::getFiles() const {
    return files;
}
