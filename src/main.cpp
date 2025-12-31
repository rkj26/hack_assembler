#include <fstream>
#include <iostream>
#include <string>

#include "Parser.h"

int main() {
    std::ifstream inputFile("../test_no_symbols.asm");
    std::ofstream outputFile("../test_no_symbols.hack");  // Output file

    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
    }

    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    Parser parser;
    std::string line;

    while (std::getline(inputFile, line)) {
        if (line.empty() || line.rfind("//", 0) == 0) continue;
        std::string binaryInstruction;
        binaryInstruction = parser.translate(line);
        outputFile << binaryInstruction << "\n";
    }

    return 0;
}