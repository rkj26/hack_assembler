#include "Parser.h"

#include <algorithm>  // for std::all_of
#include <bitset>

#include "Code.h"

std::string Parser::translate(std::string& command) {
    std::string_view val_view(command);
    if (val_view[0] == '@') {
        return translate_a_command(command);
    }
    return translate_c_command(command);
}

std::string Parser::translate_a_command(std::string& command) {
    std::string_view val_view(command);
    if (val_view[0] == '@') val_view.remove_prefix(1);

    bool is_number = std::all_of(val_view.begin(), val_view.end(), ::isdigit);

    if (is_number) {
        // Use std::stoi for standard string to int conversion
        int value = std::stoi(std::string(val_view));
        return std::bitset<16>(value).to_string();
    }

    return "Not Implemented";  // Reserved for Symbol Table logic later
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