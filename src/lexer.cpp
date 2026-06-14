#include "lexer.hpp"

#include <array>

namespace TheeCode {

    std::array<std::string, 9> KEYWORDS = {"fn", "prt", "let", "const", "for", "if", "else", "return", "while"};

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

        list.push_back(Token::make_eof());

        return list;
    }

    void Lexer::parse_word(TokenList& list) {
        std::string word = {cur()};

        next();
        while (!end()) {
            char c = cur();

            if (std::isalnum(c) || c == '_') {
                word += c;
            } else {
                break;
            }

            next();

        }

        for (auto keyword: KEYWORDS) {
            if (word == keyword) {
                list.push_back({Token::TokenType::Keyword, word});
                return;
            }
        }

        list.push_back({Token::TokenType::Identifier, word});
    }

    void Lexer::parse_string(TokenList& list) {
        // TODO: parse the entire string
    }

    void Lexer::parse_number(TokenList& list) {
        // TODO: parse an integer
    }
}