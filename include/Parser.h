#ifndef PARSER_H
#define PARSER_H

#include "Code.h"

class Parser {
   public:
    Parser(std::string& input, std::string& output);

    void read();
    void build();
    std::string translate(std::string& command);
    std::string translate_a_command(std::string& command);
    std::string translate_c_command(std::string& command);
    std::optional<std::string> get_dest(const std::string& command);
    std::optional<std::string> get_jmp(const std::string& command);
    std::string get_comp(const std::string& command);

   private:
    std::string& input;
    std::string& output;

    SymTable sym_table;
    std::vector<std::string> instructions;
    int variable_ptr;
};

#endif