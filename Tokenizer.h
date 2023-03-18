#ifndef PARSER_TOKENIZER_H
#define PARSER_TOKENIZER_H

#include <fstream>
#include <iostream>
#include <stack>

namespace xmlParser {

enum TokenType {
    LBracket,
    RBracket,
    Dash,
    TagValue,
    Value,
    EndOfFile
};

struct Token {
    TokenType type;
    std::string value;
};

class Tokenizer {
public:
    static std::stack<Token> tokenize(const std::string& filePath);
};

}


#endif
