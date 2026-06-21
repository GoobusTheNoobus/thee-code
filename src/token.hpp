#pragma once

#include <string>
#include <array>

namespace TheeCode {

    struct Token {

        enum class TokenType {
            Identifier,
            Integer,
            Float,
            String,
            Keyword,
            Operator,

            // Special symbols that isn't operator
            RoundBracket,
            SquareBracket,
            CurlyBracket,
            NewLine,
            SemiColon,
            EndOfFile
        };

        TokenType type;
        std::string data;

        inline Token(TokenType type, const std::string& data) {
            this->type = type;
            this->data = data;
        }

        inline static std::string token_type_to_string(TokenType type) {
            switch (type) {
                case TokenType::Identifier: return "Identifier";
                case TokenType::Integer: return "Integer";
                case TokenType::Float: return "Float";
                case TokenType::String: return "String";
                case TokenType::Keyword: return "Keyword";
                case TokenType::Operator: return "Operator";
                case TokenType::EndOfFile: return "EndOfFile";
                case TokenType::RoundBracket: return "RoundBracket";
                case TokenType::SquareBracket: return "SquareBracket";
                case TokenType::CurlyBracket: return "CurlyBracket";
                case TokenType::NewLine: return "NewLine";
                case TokenType::SemiColon: return "SemiColon";
                default: return "Unknown";
            }
        }

        inline static Token make_eof() {
            return Token(TokenType::EndOfFile, "");
        }

        inline std::string to_string() {
            return "{ " + token_type_to_string(type) + ", \"" + data + "\" }";
        }
    };

}