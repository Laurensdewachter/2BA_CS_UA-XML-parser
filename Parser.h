#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H

#include "ParseTable.h"
#include "Tokenizer.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

namespace xmlParser {

class CustomStack {
public:
    CustomStack() = default;

    void pushToken(Token c);
    void pushNumber(unsigned int i);

    Token popToken();
    unsigned int popNumber();

    unsigned int getTopNumber() const;

private:
    enum stackType {
        symbol,
        token
    };
    std::stack<Token> tokenStack;
    std::stack<unsigned int> numberStack;
    stackType currentStack = token;

    void changeStack();
};

class Parser {
public:
    void parseFile(std::stack<Token>& inputStack);

private:
    std::vector<char> alphabet = {'<', '>', '/', 'S', 'A', 'L', 'R', 'C'};
    ParseTable table = getParseTable();
};

}


#endif
