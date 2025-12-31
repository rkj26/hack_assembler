#include "SymTable.h"

void SymTable::add_label(std::string label, int loc) {
    symbols[label] = loc;
}

int SymTable::get_label(std::string label) {
    return symbols[label];
}

bool SymTable::contains(std::string label) {
    return symbols.find(label) != symbols.end();
}