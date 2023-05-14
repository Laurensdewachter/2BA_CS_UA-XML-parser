#ifndef PARSER_PARSETABLE_H
#define PARSER_PARSETABLE_H

#include "Tokenizer.h"
#include <map>
#include <vector>

namespace xmlParser {

    enum TableType {
        shift,
        reduction,
        error,
        accept
    };

    struct Replacement {
        TokenType left;
        std::vector<TokenType> right;
        int rule_number;
    };

    struct TableEntry {
        int shift;
        Replacement replacement;
    };

    typedef std::map<TokenType, std::vector<std::pair<TableType, TableEntry>>> ParseTable;

    ParseTable getParseTable();

}

#endif