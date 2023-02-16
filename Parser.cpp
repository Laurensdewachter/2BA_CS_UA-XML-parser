#include "Parser.h"

namespace xmlParser {

void CustomStack::pushSymbol(char c) {
    if (currentStack != symbol) {
        throw std::runtime_error("Double symbol pushed on stack");
    }
    symbolStack.push(c);
    changeStack();
}

void CustomStack::pushToken(unsigned int i) {
    if (currentStack != token) {
        throw std::runtime_error("Double token pushed on stack");
    }
    tokenStack.push(i);
    changeStack();
}

char CustomStack::popSymbol() {
    if (currentStack != token) {
        throw std::runtime_error("Double symbol popped from stack");
    }
    changeStack();
    char c = symbolStack.top();
    symbolStack.pop();
    return c;
}

unsigned int CustomStack::popToken() {
    if (currentStack != symbol) {
        throw std::runtime_error("Double token popped from stack");
    }
    changeStack();
    unsigned int i = tokenStack.top();
    tokenStack.pop();
    return i;
}

unsigned int CustomStack::topToken() const {
    if (currentStack != symbol) {
        throw std::runtime_error("Double token popped from stack");
    }
    return tokenStack.top();
}

void CustomStack::changeStack() {
    if (currentStack == symbol) currentStack = token;
    else currentStack = symbol;
}

Parser::Parser() {
    table['<'] = {{shift, TableEntry{3}},
                  {error, TableEntry{}},
                  {shift, TableEntry{3}},
                  {error, TableEntry{}},
                  {shift, TableEntry{12}},
                  {reduction, TableEntry{-1, Replacement{'A', {'C'}}}},
                  {shift, TableEntry{3}},
                  {reduction, TableEntry{-1, Replacement{'C', {'*'}}}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {reduction, TableEntry{-1, Replacement{'A', {'A', 'A'}}}},
                  {error, TableEntry{}},
                  {reduction, TableEntry{-1, Replacement{'C', {'C', 'C'}}}},
                  {shift, TableEntry{19}},
                  {reduction, TableEntry{-1, Replacement{'L', {'<', 'C', '>'}}}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {reduction, TableEntry{-1, Replacement{'A', {'L', 'A', 'R'}}}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {reduction, TableEntry{-1, Replacement{'R', {'<', '/', 'C', '>'}}}}
                  };
    table['>'] = {{error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {shift, TableEntry{15}},
                  {reduction, TableEntry{-1, Replacement{'C', {'*'}}}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {reduction, TableEntry{-1, Replacement{'C', {'C', 'C'}}}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {shift, TableEntry{22}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {shift, TableEntry{24}},
                  {error, TableEntry{}}
                  };
    table['/'] = {{error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {shift, TableEntry{17}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {shift, TableEntry{21}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}}
                  };
    table['*'] = {{error, TableEntry{}},
                  {error, TableEntry{}},
                  {shift, TableEntry{7}},
                  {shift, TableEntry{9}},
                  {shift, TableEntry{7}},
                  {reduction, TableEntry{-1, Replacement{'A', {'C'}}}},
                  {shift, TableEntry{7}},
                  {reduction, TableEntry{-1, Replacement{'C', {'*'}}}},
                  {shift, TableEntry{9}},
                  {reduction, TableEntry{-1, Replacement{'C', {'*'}}}},
                  {error, TableEntry{}},
                  {reduction, TableEntry{-1, Replacement{'A', {'A', 'A'}}}},
                  {shift, TableEntry{9}},
                  {reduction, TableEntry{-1, Replacement{'C', {'C', 'C'}}}},
                  {shift, TableEntry{7}},
                  {reduction, TableEntry{-1, Replacement{'L', {'<', 'C', '>'}}}},
                  {reduction, TableEntry{-1, Replacement{'C', {'C', 'C'}}}},
                  {shift, TableEntry{9}},
                  {reduction, TableEntry{-1, Replacement{'A', {'L', 'A', 'R'}}}},
                  {shift, TableEntry{9}},
                  {shift, TableEntry{9}},
                  {shift, TableEntry{9}},
                  {error, TableEntry{}},
                  {shift, TableEntry{9}},
                  {reduction, TableEntry{-1, Replacement{'R', {'<', '/', 'C', '>'}}}}
                  };
    table['$'] = {{error, TableEntry{}},
                  {accept, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {reduction, TableEntry{-1, Replacement{'S', {'L', 'A', 'R'}}}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {reduction, TableEntry{-1, Replacement{'R', {'<', '/', 'C', '>'}}}},
                  {error, TableEntry{}},
                  {error, TableEntry{}}
                  };
    table['S'] = {{shift, TableEntry{1}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}}
                  };
    table['A'] = {{error, TableEntry{}},
                  {error, TableEntry{}},
                  {shift, TableEntry{4}},
                  {error, TableEntry{}},
                  {error, TableEntry{11}},
                  {error, TableEntry{}},
                  {shift, TableEntry{14}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {shift, TableEntry{11}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {shift, TableEntry{11}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}}
    };
    table['L'] = {{shift, TableEntry{2}},
                  {error, TableEntry{}},
                  {shift, TableEntry{6}},
                  {error, TableEntry{}},
                  {shift, TableEntry{6}},
                  {error, TableEntry{}},
                  {shift, TableEntry{6}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {shift, TableEntry{6}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {shift, TableEntry{6}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}}
    };
    table['R'] = {{error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {shift, TableEntry{10}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {shift, TableEntry{18}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {error, TableEntry{}}
    };
    table['C'] = {{error, TableEntry{}},
                  {error, TableEntry{}},
                  {shift, TableEntry{5}},
                  {shift, TableEntry{8}},
                  {shift, TableEntry{5}},
                  {shift, TableEntry{13}},
                  {shift, TableEntry{5}},
                  {error, TableEntry{}},
                  {shift, TableEntry{16}},
                  {error, TableEntry{}},
                  {error, TableEntry{}},
                  {shift, TableEntry{5}},
                  {shift, TableEntry{8}},
                  {shift, TableEntry{13}},
                  {shift, TableEntry{5}},
                  {error, TableEntry{}},
                  {shift, TableEntry{16}},
                  {shift, TableEntry{20}},
                  {error, TableEntry{}},
                  {shift, TableEntry{8}},
                  {shift, TableEntry{16}},
                  {shift, TableEntry{23}},
                  {error, TableEntry{}},
                  {shift, TableEntry{16}},
                  {error, TableEntry{}}
    };

    alphabet = {'<', '>', '/', 'S', 'A', 'L', 'R', 'C'};
}

void Parser::parseFile(const std::string& filePath) {
    std::ifstream stream(filePath);
    std::string input;
    std::string inputLine;
    while (getline(stream, inputLine)) {
        for (auto c : inputLine) {
            if (c != ' ' && c != '\n' && c != '\t') {
                input.push_back(c);
            }
        }
    }
    input += '$';
    std::stack<char> inputStack;
    for (int i = input.size()-1; i >= 0; i--) {
        inputStack.push(input[i]);
    }
    CustomStack stack;
    unsigned int token = 0;
    stack.pushToken(token);

    char symbol = inputStack.top();
    inputStack.pop();

    if (!charInAlphabet(symbol) && !isLetter(symbol)) {
        throw std::runtime_error("Invalid symbol in input");
    }
    if (isLetter(symbol)) {
        symbol = '*';
    }

    std::pair<TableType, TableEntry> entry = table[symbol][token];

    while (entry.first != accept) {
        switch (entry.first) {
            case shift:
                stack.pushSymbol(symbol);
                token = entry.second.shift;
                stack.pushToken(token);
                symbol = inputStack.top();
                if (isLetter(symbol)) {
                    symbol = '*';
                }
                inputStack.pop();

                entry = table[symbol][token];
                break;

            case reduction: {
                Replacement replacement = entry.second.replacement;
                std::reverse(replacement.right.begin(), replacement.right.end());
                for (auto c: replacement.right) {
                    stack.popToken();
                    stack.popSymbol();
                }
                token = stack.topToken();
                stack.pushSymbol(replacement.left);
                token = table[replacement.left][token].second.shift;
                stack.pushToken(token);
                entry = table[symbol][token];
                break;
            }

            case error:
                throw std::runtime_error("There is an error in the input");
                break;

            case accept:
                break;
        }
    }
    std::cout << "Input is a correct xml file" << std::endl;
}

bool Parser::isLetter(char c) const {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool Parser::charInAlphabet(char c) const {
    return std::find(alphabet.begin(), alphabet.end(), c) != alphabet.end();
}

}
