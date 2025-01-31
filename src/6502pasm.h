#pragma once
#include <string>
#include <vector>
#include <regex>

// patterns
std::regex labelPattern("([a-zA-Z0-9_]):");
std::regex instructionPattern("^\\s*([a-zA-Z]+)( ([^,]*)(,(\\w))?)?\\s*$");

enum AddressMode {
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
    ADDR_IMPLIED
};

enum LineType {
    LINE_UNKNOWN,
    LINE_EMPTY,
    LINE_INSTRUCTION,
    LINE_LABEL,
};


class Assembler {
public:
    std::vector<std::string> input_lines;
    std::vector<char> output;

    Assembler() {}

    LineType getLineType(std::string line);

    int assembleInstruction();

    int assemble();
};