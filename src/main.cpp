#include <fstream>
#include <iostream>
#include <string>

#include "Parser.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename.asm>" << std::endl;
        return 1;
    }

    std::string input_filename = argv[1];
    std::string output_filename;

    size_t last_dot = input_filename.find_last_of(".");

    if (last_dot == std::string::npos) {
        output_filename = input_filename + ".hack";
    } else {
        output_filename = input_filename.substr(0, last_dot) + ".hack";
    }

    std::cout << "Starting the assembler for input:  " << input_filename << std::endl;

    Parser parser = Parser{input_filename, output_filename};
    parser.read();
    parser.build();

    std::cout << "Assembler run was successful! See output: " << output_filename << std::endl;

    return 0;
}