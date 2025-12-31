#include "Code.h"

// ==========================================
// 1. Initialize Static Hash Maps
// ==========================================

// The "comp" table maps the mnemonic to the 7-bit binary code (a c1 c2 c3 c4 c5 c6).
// The first bit (a) is 0 for operations using A, and 1 for operations using M.
const std::unordered_map<std::string, std::string> Code::comp_table = {
    // a = 0 (Calculations involving A register)
    {"0", "0101010"},
    {"1", "0111111"},
    {"-1", "0111010"},
    {"D", "0001100"},
    {"A", "0110000"},
    {"!D", "0001101"},
    {"!A", "0110001"},
    {"-D", "0001111"},
    {"-A", "0110011"},
    {"D+1", "0011111"},
    {"A+1", "0110111"},
    {"D-1", "0001110"},
    {"A-1", "0110010"},
    {"D+A", "0000010"},
    {"D-A", "0010011"},
    {"A-D", "0000111"},
    {"D&A", "0000000"},
    {"D|A", "0010101"},

    // a = 1 (Calculations involving Memory[A])
    {"M", "1110000"},
    {"!M", "1110001"},
    {"-M", "1110011"},
    {"M+1", "1110111"},
    {"M-1", "1110010"},
    {"D+M", "1000010"},
    {"D-M", "1010011"},
    {"M-D", "1000111"},
    {"D&M", "1000000"},
    {"D|M", "1010101"}};

// The "dest" table maps the mnemonic to the 3-bit destination code (d1 d2 d3).
const std::unordered_map<std::string, std::string> Code::dest_table = {
    {"null", "000"}, {"M", "001"},  {"D", "010"},  {"MD", "011"},
    {"A", "100"},    {"AM", "101"}, {"AD", "110"}, {"AMD", "111"}};

// The "jump" table maps the mnemonic to the 3-bit jump code (j1 j2 j3).
const std::unordered_map<std::string, std::string> Code::jump_table = {
    {"null", "000"}, {"JGT", "001"}, {"JEQ", "010"}, {"JGE", "011"},
    {"JLT", "100"},  {"JNE", "101"}, {"JLE", "110"}, {"JMP", "111"}};

// ==========================================
// 2. Implement Conversion Methods
// ==========================================

std::string Code::convert_comp(const std::string& mnemonic) {
    if (comp_table.find(mnemonic) != comp_table.end()) {
        return comp_table.at(mnemonic);
    }
    // Return "0000000" or handle error if the mnemonic is invalid.
    // In a robust system, you might throw an exception here.
    return "0000000";
}

std::string Code::convert_dest(const std::optional<std::string>& mnemonic) {
    // If no destination is specified (e.g., "D;JMP"), the dest bits are 000.
    if (!mnemonic.has_value()) {
        return "000";
    }

    const std::string& m = mnemonic.value();
    if (dest_table.find(m) != dest_table.end()) {
        return dest_table.at(m);
    }
    return "000";
}

std::string Code::convert_jump(const std::optional<std::string>& mnemonic) {
    // If no jump is specified (e.g., "D=M"), the jump bits are 000.
    if (!mnemonic.has_value()) {
        return "000";
    }

    const std::string& m = mnemonic.value();
    if (jump_table.find(m) != jump_table.end()) {
        return jump_table.at(m);
    }
    return "000";
}