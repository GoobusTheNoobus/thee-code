#pragma once

#include <vector>
#include <string>

#include "token.hpp"

namespace TheeCode {

    using TokenList = std::vector<Token>;

    class Lexer {
        
        public:
        Lexer(std::string file) : file(file), len(file.size()) {};

        TokenList tokenize();

        private:
        std::string file;
        int len;
        int index = 0;

        inline void next() { ++index; }
        inline char current() { return file[index]; }
        inline char peek() { return file[index + 1]; }
        inline bool end() { return index >= len; }

        // Helpers used in parsing
        // We pass a reference of the token list used within the main tokenize() function.
        void parse_word(TokenList& list);
        void parse_number(TokenList& list);
        void parse_string(TokenList& list);

    };

}