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

    TreeNode *Parser::parseFile(std::stack<Token> &inputStack) {
        CustomStack stack;
        unsigned int shiftNumber = 0;
        stack.pushNumber(shiftNumber);

        std::stack<TreeNode *> node_stack;
        TreeNode *root = nullptr;

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

                    Token popped_token;
                    TreeNode* new_node;
                    switch (replacement.rule_number) {
                        case 1:
                            stack.popNumber();
                            popped_token = stack.popToken();
                            stack.popNumber();
                            stack.popToken();
                            stack.popNumber();
                            stack.popToken();

                            root = node_stack.top();
                            node_stack.pop();
                            root->addChild(node_stack.top());
                            node_stack.pop();
                            node_stack.pop();

                            shiftNumber = stack.getTopNumber();
                            shiftNumber = table[S][shiftNumber].second.shift;
                            stack.pushToken({S, popped_token.value});
                            stack.pushNumber(shiftNumber);
                            break;
                        case 2:
                            stack.popNumber();
                            popped_token = stack.popToken();

                            shiftNumber = stack.getTopNumber();
                            shiftNumber = table[A][shiftNumber].second.shift;
                            stack.pushToken({A, popped_token.value});
                            stack.pushNumber(shiftNumber);
                            break;
                        case 3:
                            stack.popNumber();
                            stack.popToken();
                            stack.popNumber();
                            popped_token = stack.popToken();

                            new_node = new TreeNode("dummy", false);
                            for (unsigned int i = 0; i < 2; i++) {
                                new_node->addChild(node_stack.top());
                                node_stack.pop();
                            }
                            node_stack.push(new_node);

                            shiftNumber = stack.getTopNumber();
                            shiftNumber = table[A][shiftNumber].second.shift;
                            stack.pushToken({A, ""});
                            stack.pushNumber(shiftNumber);
                            break;
                        case 4:
                            stack.popNumber();
                            popped_token = stack.popToken();
                            stack.popNumber();
                            stack.popToken();
                            stack.popNumber();
                            stack.popToken();

                            new_node = node_stack.top();
                            node_stack.pop();
                            new_node->addChild(node_stack.top());
                            node_stack.pop();
                            node_stack.pop();
                            node_stack.push(new_node);

                            shiftNumber = stack.getTopNumber();
                            shiftNumber = table[A][shiftNumber].second.shift;
                            stack.pushToken({A, popped_token.value});
                            stack.pushNumber(shiftNumber);
                            break;
                        case 5:
                            stack.popNumber();
                            stack.popToken();
                            stack.popNumber();
                            popped_token = stack.popToken();
                            stack.popNumber();
                            stack.popToken();

                            shiftNumber = stack.getTopNumber();
                            shiftNumber = table[L][shiftNumber].second.shift;
                            stack.pushToken({L, popped_token.value});
                            stack.pushNumber(shiftNumber);
                            break;
                        case 6:
                            stack.popNumber();
                            stack.popToken();
                            stack.popNumber();
                            stack.popToken();
                            stack.popNumber();
                            popped_token = stack.popToken();
                            stack.popNumber();
                            stack.popToken();

                            shiftNumber = stack.getTopNumber();
                            shiftNumber = table[R][shiftNumber].second.shift;
                            stack.pushToken({R, popped_token.value});
                            stack.pushNumber(shiftNumber);
                            break;
                        case 7:
                            stack.popNumber();
                            popped_token = stack.popToken();

                            new_node = new TreeNode(popped_token.value, true);
                            node_stack.push(new_node);

                            shiftNumber = stack.getTopNumber();
                            shiftNumber = table[C][shiftNumber].second.shift;
                            stack.pushToken({C, popped_token.value});
                            stack.pushNumber(shiftNumber);
                            break;
                        case 8:
                            stack.popNumber();
                            popped_token = stack.popToken();

                            new_node = new TreeNode(popped_token.value, false);
                            node_stack.push(new_node);

                            shiftNumber = stack.getTopNumber();
                            shiftNumber = table[D][shiftNumber].second.shift;
                            stack.pushToken({D, popped_token.value});
                            stack.pushNumber(shiftNumber);
                            break;
                    }

                    entry = table[token.type][shiftNumber];
                    break;
                }

                case error:
                    throw std::runtime_error("There is an error in the input");
            }
        }
        if (token.type == EndOfFile) {
            return root;
        } else {
            throw std::runtime_error("There is an error in the input");
        }
    }

}
