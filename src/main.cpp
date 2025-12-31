#include <fstream>
#include <iostream>
#include <string>

#include "Parser.h"

int main() {
    std::string input_filename = "../pong.asm";
    std::string output_filename = "../pong.hack";

    Parser parser = Parser{input_filename, output_filename};
    parser.read();
    parser.build();

    return 0;
}