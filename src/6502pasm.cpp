#include <stdio.h>
#include <string>
#include <vector>
#include <regex>
#include "6502pasm.h"


std::regex labelPattern("([a-zA-Z0-9_]+):\\s*");
std::regex instructionPattern("^\\s*([a-zA-Z]+)( ([^,]*)(,(\\w))?)?\\s*$");
std::regex directivePattern("\\s*\\.(\\w+)(\\s+(.+))?");

int Assembler::assemble() {
    for (int lineIdx=0;lineIdx<input_lines.size();lineIdx++) {
        std::string line = input_lines[lineIdx];
        bool hasComment = false;
        int commentIndex = -1;
        for (int i=0;i<line.size();i++) {
            if (line[i]==';') {
                hasComment = true;
                commentIndex = i;
                break;
            }
        }
        std::string lineNoComment = line.substr(0,commentIndex);
        LineType lineType = getLineType(lineNoComment);
        if (lineType == LINE_UNKNOWN) {
            printf("Unknown line: '%s'\n",line.c_str());
        }
    }
    return 0;
}

LineType Assembler::getLineType(std::string line) {
    if (line.size()==0) {
        return LINE_EMPTY;
    }
    if (std::regex_match(line,directivePattern)) {
        return LINE_DIRECTIVE;
    }
    if (std::regex_match(line,instructionPattern)) {
        return LINE_INSTRUCTION;
    }
    if (std::regex_match(line,labelPattern)) {
        return LINE_LABEL;
    }
    return LINE_UNKNOWN;
}

int Assembler::parseLabel(std::string line) {
    return 0;
}