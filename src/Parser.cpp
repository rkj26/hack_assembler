#include "Parser.h"

#include <algorithm>  // for std::all_of
#include <bitset>
#include <fstream>
#include <iostream>
#include <string>

#include "Code.h"

Parser::Parser(std::string& input, std::string& output)
    : input(input), output(output), variable_ptr(16) {}

void Parser::read() {
    std::ifstream inputFile(input);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << input << std::endl;
        return;
    }

    std::string line;

    // --- PASS 1: Read instructions and Labels (L-commands) ---
    while (std::getline(inputFile, line)) {
        // Remove whitespace/comments (simplified cleanup)
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        if (line.empty() || line.rfind("//", 0) == 0) continue;

        // Remove trailing comments if they exist inline "D=M // comment"
        size_t comment_pos = line.find("//");
        if (comment_pos != std::string::npos) {
            line = line.substr(0, comment_pos);
            // Trim trailing spaces after removing comment
            line.erase(line.find_last_not_of(" \t\r\n") + 1);
        }

        if (line.find('(') == 0) {
            size_t end_pos = line.find(')');
            std::string label = line.substr(1, end_pos - 1);

            // Use vector size as address
            Parser::sym_table.add_label(label, Parser::instructions.size());
            continue;
        }

        Parser::instructions.push_back(line);
    }

    for (const auto& instr : Parser::instructions) {
        if (instr[0] == '@') {
            std::string_view val_view(instr);
            val_view.remove_prefix(1);  // Remove '@'

            bool is_number = std::all_of(val_view.begin(), val_view.end(), ::isdigit);

            if (!is_number) {
                std::string label(val_view);  // Convert view to string

                if (!Parser::sym_table.contains(label)) {
                    Parser::sym_table.add_label(label, variable_ptr);
                    variable_ptr++;
                }
            }
        }
    }
}

void Parser::build() {
    std::ofstream outputFile(output);
    for (auto& instruction : Parser::instructions) {
        std::string binaryInstruction = translate(instruction);
        outputFile << binaryInstruction << "\n";
    }
}

std::string Parser::translate(std::string& command) {
    if (command[0] == '@') {
        return translate_a_command(command);
    }
    return translate_c_command(command);
}

std::string Parser::translate_a_command(std::string& command) {
    std::string_view val_view(command);
    val_view.remove_prefix(1);  // Remove '@'

    bool is_number = std::all_of(val_view.begin(), val_view.end(), ::isdigit);

    int value;
    if (is_number) {
        value = std::stoi(std::string(val_view));
    } else {
        // Convert view to string for the map lookup
        std::string label(val_view);
        value = Parser::sym_table.get_label(label);
    }

    return std::bitset<16>(value).to_string();
}

std::optional<std::string> Parser::get_dest(const std::string& command) {
    auto pos = command.find('=');
    if (pos == std::string::npos) {
        return std::nullopt;
    }
    return command.substr(0, pos);
}

std::optional<std::string> Parser::get_jmp(const std::string& command) {
    auto pos = command.find(';');
    if (pos == std::string::npos) {
        return std::nullopt;
    }
    return command.substr(pos + 1);
}

std::string Parser::get_comp(const std::string& command) {
    auto eq_pos = command.find('=');
    size_t start_index = (eq_pos == std::string::npos) ? 0 : eq_pos + 1;

    auto semi_pos = command.find(';');
    size_t end_index = (semi_pos == std::string::npos) ? command.length() : semi_pos;

    return command.substr(start_index, end_index - start_index);
}

std::string Parser::translate_c_command(std::string& command) {
    std::string comp = get_comp(command);
    std::optional<std::string> dest = get_dest(command);
    std::optional<std::string> jmp = get_jmp(command);

    return "111" + Code::convert_comp(comp) + Code::convert_dest(dest) + Code::convert_jump(jmp);
}