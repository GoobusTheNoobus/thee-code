#include <iostream>
#include <fstream>
#include <sstream>

#include "misc.hpp"
#include "error.hpp"
#include "lexer.hpp"

using namespace TheeCode;

// Running without any arguments will print a guide on how to use
// the app, while running with a filename will result in it running
// that file.
int main(int argc, char** argv) {
    // No arguments
    if (argc == 1) {
        std::cout << "\nTheeCode is a language that is very bad. For more information, check out README.md. \n"
                  << "Developer list can also be found in README.md.\n" 
                  << "\n"
                  << "To run an app, run: \n" 
                  << "   theecode app.thcd\n" 
                  << "\nThat's basically it. Goobye now!\n" 
                  << std::endl; 
        return 0;
    } else {
        std::string filename = argv[1];
        std::ifstream file(filename);

        if (!file.is_open()) {
            raise_error(ErrorType::CannotOpenFileError, "Failed to open \"" + filename + '"');
        }

        std::cout << GREEN << "[TheeCode]: Successfully opened file!" << RESET << std::endl;
        std::cout << "Converting file to string...\n";
        
        std::stringstream buffer;
        buffer << file.rdbuf();

        Lexer jerry(buffer.str());
        
        std::cout << "Tokenizing...\n";

        TokenList tokens = jerry.tokenize();
        
        for (Token token : tokens) {
            std::cout << token.to_string() << std::endl;
        }
    }

    return 0;
}
