#include "Parser.h"

namespace xmlParser {

    void CustomStack::pushToken(Token c) {
        if (currentStack != symbol) {
            throw std::runtime_error("Double symbol pushed on stack");
        }
        tokenStack.push(c);
        changeStack();
    }

    void CustomStack::pushNumber(unsigned int i) {
        if (currentStack != token) {
            throw std::runtime_error("Double token pushed on stack");
        }
        numberStack.push(i);
        changeStack();
    }

    Token CustomStack::popToken() {
        if (currentStack != token) {
            throw std::runtime_error("Double symbol popped from stack");
        }
        changeStack();
        Token c = tokenStack.top();
        tokenStack.pop();
        return c;
    }

    unsigned int CustomStack::popNumber() {
        if (currentStack != symbol) {
            throw std::runtime_error("Double token popped from stack");
        }
        changeStack();
        unsigned int i = numberStack.top();
        numberStack.pop();
        return i;
    }

    unsigned int CustomStack::getTopNumber() const {
        if (currentStack != symbol) {
            throw std::runtime_error("Double token popped from stack");
        }
        return numberStack.top();
    }

    void CustomStack::changeStack() {
        if (currentStack == symbol) currentStack = token;
        else currentStack = symbol;
    }

    void Parser::parseFile(std::stack<Token> &inputStack) {
        CustomStack stack;
        unsigned int shiftNumber = 0;
        stack.pushNumber(shiftNumber);

        Token token = inputStack.top();
        inputStack.pop();

        std::pair<TableType, TableEntry> entry = table[token.type][shiftNumber];

        while (entry.first != accept) {
            switch (entry.first) {
                case shift:
                    stack.pushToken(token);
                    shiftNumber = entry.second.shift;
                    stack.pushNumber(shiftNumber);

                    token = inputStack.top();
                    inputStack.pop();

                    entry = table[token.type][shiftNumber];
                    break;

                case reduction: {
                    Replacement replacement = entry.second.replacement;
                    for (auto &c: replacement.right) {
                        stack.popNumber();
                        stack.popToken();
                    }
                    shiftNumber = stack.getTopNumber();
                    shiftNumber = table[replacement.left][shiftNumber].second.shift;

                    // TODO: create TreeNode objects here

                    stack.pushToken({replacement.left, ""});
                    stack.pushNumber(shiftNumber);

                    entry = table[token.type][shiftNumber];
                    break;
                }

                case error:
                    throw std::runtime_error("There is an error in the input");
            }
        }
        if (token.type == EndOfFile) {
            return;
        } else {
            throw std::runtime_error("There is an error in the input");
        }
    }

}
