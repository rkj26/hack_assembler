#pragma once

#include "SymTable.h"

class Code {
   public:
    // Make methods static. No need to instantiate a 'Code' object.
    static std::string convert_comp(const std::string& mnemonic);
    static std::string convert_dest(const std::optional<std::string>& mnemonic);
    static std::string convert_jump(const std::optional<std::string>& mnemonic);

   private:
    static const std::unordered_map<std::string, std::string> comp_table;
    static const std::unordered_map<std::string, std::string> dest_table;
    static const std::unordered_map<std::string, std::string> jump_table;
};