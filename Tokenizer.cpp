#include "Tokenizer.h"

namespace xmlParser {

    std::stack<Token> Tokenizer::tokenize(const std::string &filePath) {
        std::ifstream stream(filePath);
        std::string input;
        std::string inputLine;
        while (getline(stream, inputLine)) {
            for (auto c: inputLine) {
                if (c != ' ' && c != '\n' && c != '\t') {
                    input.push_back(c);
                }
            }
        }

        std::stack<Token> tokenStack;
        std::string currentWord;
        for (auto c: input) {
            switch (c) {
                case '<':
                    if (!currentWord.empty()) {
                        tokenStack.push({Value, currentWord});
                        currentWord.clear();
                    }
                    tokenStack.push({LBracket});
                    break;
                case '>':
                    if (!currentWord.empty()) {
                        tokenStack.push({TagValue, currentWord});
                        currentWord.clear();
                    }
                    tokenStack.push({RBracket});
                    break;
                case '/':
                    tokenStack.push({Dash});
                    break;
                default:
                    currentWord.push_back(c);
                    break;
            }
        }
        tokenStack.push({EndOfFile});

        std::stack<Token> reversedStack;
        while (!tokenStack.empty()) {
            reversedStack.push(tokenStack.top());
            tokenStack.pop();
        }

        return reversedStack;
    }

}
