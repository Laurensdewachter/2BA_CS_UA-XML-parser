#include "Parser.h"
#include "Tokenizer.h"

int main() {
    auto tokens = xmlParser::Tokenizer::tokenize("input.xml");
    xmlParser::Parser parser;
    TreeNode *ast = parser.parseFile(tokens);
    ast->removeDummy();

    return 0;
}
