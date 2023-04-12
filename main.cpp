#include "Parser.h"
#include "Tokenizer.h"

int main() {
    auto tokens = xmlParser::Tokenizer::tokenize("input.xml");
    xmlParser::Parser parser;
    parser.parseFile(tokens);

    return 0;
}
