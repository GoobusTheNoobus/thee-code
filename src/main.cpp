#include <iostream>
#include <fstream>

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
                  << "   theecode app.kkz\n" 
                  << "\nThat's basically it. Goobye now!\n" 
                  << std::endl; 
        return 0;
    } else {
        std::string filename = argv[1];
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "\n\033[31m" << "[TheeCode]: Failed to open file " << filename << "\033[0m\n" << std::endl;
            return 1;
        }

        std::cout << "\n\033[32m" << "[TheeCode]: Successfully opened file!" << "\033[0m\n" << std::endl;
        
    }

    return 0;
}