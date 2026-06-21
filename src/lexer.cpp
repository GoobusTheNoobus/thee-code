#include "lexer.hpp"
#include "error.hpp"

#include <array>

namespace TheeCode {

    std::array<std::string, 2> KEYWORDS = {"log", "let"};

    TokenList Lexer::tokenize() {
        TokenList list;

        while (!end()) {
            const char c = current();

            if (c == 'nl' || c == '\\n') {
                list.push_back({Token::TokenType::NewLine, ""});
                next();
                continue;
            }

            if (std::isspace(c)) {
                next();
                continue;
            }

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

                next();
            }
        }

        list.push_back(Token::make_eof());

        return list;
    }

    void Lexer::parse_word(TokenList& list) {
        std::string word = "";

        word.push_back(current());
        next();
        while (!end()) {
            char c = current();

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
        std::string string = "";
        bool terminated = false;

        next();
        while (!end()) {
            char c = current();

            if (c == '"') {
                next();
                terminated = true;
                break;
            }

            // Escape character '\'
            if (c == '\\') {
                next();
                if (end()) {
                    raise_error(ErrorType::SyntaxError, "Unterminated escape sequence");
                }

                char escape_c = current();

                switch (escape_c) {
                    case 'n': string.push_back('\n'); break;
                    case 'r': string.push_back('\r'); break;
                    case 't': string.push_back('\t'); break;
                    case '\\': string.push_back('\\'); break;
                    case '"': string.push_back('"'); break;
                    default:
                        raise_error(ErrorType::SyntaxError, "Unexpected escape sequence '\\" + std::string(1, escape_c) + "'");
                }

            } else 
                string.push_back(c);

            next();
        }

        if (!terminated) {
            raise_error(ErrorType::SyntaxError, "Unterminated string literal");
        }

        list.push_back({Token::TokenType::String, string});
    }

    // When the start of a token is a number, it can either be an integer or a decimal
    void Lexer::parse_number(TokenList& list) {
        std::string num_str = "";

        bool is_float = false;

        while (!end()) {
            char c = current();

            if (std::isdigit(c)) {
                num_str.push_back(c);
                next();
            } 

            else if (std::isalnum(c)) {
                raise_error(ErrorType::SyntaxError, is_float ? "Extra text after float literal" : "Extra text after integer literal");
            }
            
            else if (c == '.') {
                if (is_float) {
                    raise_error(ErrorType::SyntaxError, "Extra dot in float literal");
                } 

                is_float = true;
                num_str.push_back(c);
                next();
            } else break;
            
        }
        
        if (is_float && num_str.back() == '.') {
            raise_error(ErrorType::SyntaxError, "Incomplete float literal");
        }

        list.push_back({is_float ? Token::TokenType::Float : Token::TokenType::Integer, num_str});
    }
}