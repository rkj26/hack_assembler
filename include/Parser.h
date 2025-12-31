#ifndef PARSER_H
#define PARSER_H

#include "Code.h"

enum class COMMAND_TYPE { A_COMMAND, C_COMMAND, L_COMMAND };

class Parser {
   public:
    // Parser(std::string filename);

    bool hasMoreCommands();

    // Declaration only
    std::string translate(std::string& command);
    std::string translate_a_command(std::string& command);
    std::string translate_c_command(std::string& command);
    std::optional<std::string> get_dest(const std::string& command);
    std::optional<std::string> get_jmp(const std::string& command);
    std::string get_comp(const std::string& command);
};

#endif