#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

namespace xmlParser {

enum TableType {
    shift,
    reduction,
    error,
    accept
};

struct Replacement {
    char left;
    std::vector<char> right;
};

struct TableEntry {
    int shift;
    Replacement replacement;
};

typedef std::map<char, std::vector<std::pair<TableType, TableEntry>>> ParseTable;

class CustomStack {
public:
    CustomStack() = default;

    void pushSymbol(char c);
    void pushToken(unsigned int i);

    char popSymbol();
    unsigned int popToken();

    unsigned int topToken() const;

private:
    enum stackType {
        symbol,
        token
    };
    std::stack<char> symbolStack;
    std::stack<unsigned int> tokenStack;
    stackType currentStack = token;

    void changeStack();
};

class Parser {
public:
    Parser();

    void parseFile(const std::string& filePath);

private:
    std::vector<char> alphabet;
    ParseTable table;

    bool isLetter(char c) const;
    bool charInAlphabet(char c) const;
};

}


#endif
