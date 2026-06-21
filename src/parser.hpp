#pragma once

#include "lexer.hpp"
#include "error.hpp"
#include "ast.hpp"

#include <memory>

namespace TheeCode {

    class Parser {
        public:
        Parser(const TokenList& tokens) : tokens(tokens), len(tokens.size()) {};
        ASTReference parse();

        private:
        TokenList tokens;
        size_t index = 0;
        size_t len;

        inline Token& next() { return tokens[index++]; }
        inline Token& current() { return tokens[index]; }
        inline Token& peek() { return tokens[index + 1]; }
        inline bool end() { return index >= len; }

        ASTReference parse_statement();
        ASTReference parse_variable_decl();
        ASTReference parse_expression();
        ASTReference parse_log_statement();

    };
}