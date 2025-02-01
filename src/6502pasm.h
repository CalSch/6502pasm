#pragma once
#include <string>
#include <vector>
#include <regex>

#define DEBUG 0

// patterns
extern std::regex labelPattern;
extern std::regex instructionPattern;
extern std::regex directivePattern;

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
    LINE_DIRECTIVE,
};

struct Label {
    std::string name;
    int location;
};

class Assembler {
public:
    std::vector<std::string> input_lines;
    std::vector<char> output;

    std::vector<Label> labels;

    Assembler() {}

    LineType getLineType(std::string line);

    int parseLabel(std::string line);

    int assembleInstruction();

    int assemble();
};