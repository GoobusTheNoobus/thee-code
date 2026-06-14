#include "lexer.hpp"

namespace TheeCode {

    TokenList Lexer::tokenize() {
        TokenList list;

        while (!end()) {
            const char c = cur();

            if (std::isalpha(c) || c == '_') {
                parse_word(list);
            } else if (std::isdigit(c)) {
                parse_number(list);
            } else if (c == '"') {
                parse_string(list);
            } else {
                if (c == '(' || c == ')') {
                    list.push_back({Token::TokenType::RoundBracket, {c}});
                } else if (c == '[' || c == ']') {
                    list.push_back({Token::TokenType::SquareBracket, {c}});
                } else if (c == '{' || c == '}') {
                    list.push_back({Token::TokenType::CurlyBracket, {c}});
                } else {
                    list.push_back({Token::TokenType::Operator, {c}});
                }
            }
        }

        return list;
    }
}