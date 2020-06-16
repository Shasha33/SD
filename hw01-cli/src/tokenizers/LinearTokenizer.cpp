#include <tokenizers/LinearTokenizer.h>

Token LinearTokenizer::nextToken() {
    if (pointer == (int) s.size()) {
        pointer++;
        return Token(TokenType::END);
    }
    if (std::isspace(s[pointer])) { // is space?
        pointer++;
        return Token(TokenType::SPACE, " ");
    }
    if (auto foundToken = specialSymbols.find(s[pointer]);
            foundToken != specialSymbols.end()) {
        pointer++;
        return foundToken->second;
    }
    std::optional<char> lastQuote;
    std::string tokenContent;
    for (int &i = pointer; i < (int) s.size(); i++) {
        if (!lastQuote.has_value() && (std::isspace(s[i]) || specialSymbols.count(s[i]))) {
            break;
        }
        tokenContent.push_back(s[i]);
        if (s[i] == '"' || s[i] == '\'') { // is quote?
            if (lastQuote.has_value()) {
                if (lastQuote.value() == s[i]) {
                    lastQuote.reset();
                }
            } else {
                lastQuote = s[i];
            }
        }
    }
    return Token(TokenType::LITERAL, tokenContent);
}

bool LinearTokenizer::hasNextToken() {
    return pointer <= (int) s.size();
}

void LinearTokenizer::append(const std::string &s) {
    this->s += s;
}

void LinearTokenizer::clear() {
    s.clear();
    pointer = 0;
}
