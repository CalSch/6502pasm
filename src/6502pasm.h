#pragma once
#include <string>
#include <vector>
#include <regex>

#define DEBUG 1

#define IS_HEX_CHAR(c) ((c>='0' && c<='9') || (c>='a' && c<='f') || (c>='A' && c<='F'))

// patterns
extern std::regex labelPattern;
extern std::regex instructionPattern;
extern std::regex directivePattern;

extern std::regex immediatePattern;
extern std::regex zeropagePattern;
extern std::regex absolutePattern;
extern std::regex indirectPattern;

enum AddressMode {
    ADDR_INVALID, // For syntax errors
    ADDR_IMPLIED,
    ADDR_ACCUMULATOR,
    ADDR_IMMEDIATE,
    ADDR_ZERO_PAGE,
    ADDR_ZERO_PAGE_X,
    ADDR_ZERO_PAGE_Y,
    ADDR_ABSOLUTE,
    ADDR_ABSOLUTE_X,
    ADDR_ABSOLUTE_Y,
    ADDR_INDIRECT,
    ADDR_INDIRECT_X,
    ADDR_INDIRECT_Y,
};

enum LineType {
    LINE_UNKNOWN, // For syntax errors
    LINE_EMPTY,
    LINE_INSTRUCTION,
    LINE_LABEL,
    LINE_DIRECTIVE,
};

struct Macro {
    std::string name;
    std::string text;
};

struct Label {
    std::string name;
    int location;
};

struct Address {
    AddressMode addrMode;
    int location;
    std::string label;
};

struct Instruction {
    std::string mnemonic;
    Address addr;
};

class Assembler {
public:
    std::vector<std::string> input_lines;
    std::vector<char> output;

    std::vector<Label> labels;
    std::vector<Macro> macros;

    Assembler() {}

    LineType getLineType(std::string line);

    // Turns a string into an `Address`
    Address parseAddress(std::string addr);
    // Create and add a `Label` struct from a line
    // Note: implies that the `labelPattern` already matches the line (No error handling!)
    Label parseLabel(std::string line);
    Instruction parseInstruction(std::string line);

    int assembleInstruction(Instruction inst);

    int assemble();
};