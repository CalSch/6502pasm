#include <stdio.h>
#include <string>
#include <vector>
#include <regex>
#include "6502pasm.h"


std::regex labelPattern("([a-zA-Z0-9_]+):\\s*");
std::regex instructionPattern("^\\s*([a-zA-Z]+)( (([^,\\s]*)(,(\\w))?))?\\s*$");
std::regex directivePattern("\\s*\\.(\\w+)(\\s+(.+))?");

std::regex immediatePattern("#\\$[0-9a-fA-F]{2}"); // #$BB (BB=byte)
std::regex zeropagePattern("\\$[0-9a-fA-F]{2}");   //  $LL (LL=low byte of addr)
std::regex absolutePattern("\\$[0-9a-fA-F]{4}");   //  $HHLL (HHLL = full addr)
// std::regex indirectPattern("\\(\\$[0-9a-fA-F]{4}\\)");

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
        if (lineType == LINE_LABEL) {
            parseLabel(lineNoComment);
        }
        if (lineType == LINE_INSTRUCTION) {
            parseInstruction(lineNoComment);
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

Label Assembler::parseLabel(std::string line) {
    std::smatch m;
    std::regex_match(line,m,labelPattern);

    if (DEBUG) {
        printf("Parsing label: '%s'\n",line.c_str());
        int i=0;
        for (auto group : m) {
            printf("\tgroup %d: '%s'\n",i,group.str().c_str());
            i++;
        }
    }

    std::string name = m[1];
    return (Label){name,-1}; // location is unknown for now
}

Address Assembler::parseAddress(std::string str) {
    if (str[0] == '%') { // it's a macro!
        std::string macroName = str.substr(1); // get all characters after %
        // Find the macro
        Macro macro;
        bool found = false;
        for (int i=0;i<macros.size();i++) {
            if (macros[i].name==macroName) {
                macro = macros[i];
                found = true;
                break;
            }
        }
        if (!found) {
            //TODO: error
        } else {
            str = macro.text; // Replace text and continue
        }
    }
    if (str[0] == '#' && str[1] == '$' && str.size() == 4) { // Immediate (#$BB)
        return (Address){
            ADDR_IMMEDIATE,
            stoi(str.substr(2,2),0,16) // convert hex str to int
        };
    }
    if (str[0] == '$') {
        if (str.size()==3) { // zeropage or relative, no index ($LL or $BB)
            return (Address){
                ADDR_ZERO_PAGE, // just returns zeropage, but later it will be converted into relative if its a branch instruction
                stoi(str.substr(1,2),0,16) // convert hex str to int
            };
        }
        if (str.size()==5) { // Either absolute no index or zeropage with index
            // Now find which one!
            if (str[3]==',') { // it's zeropage indexed!
                if (str[4]=='X') {
                    return (Address){
                        ADDR_ZERO_PAGE_X,
                        stoi(str.substr(1,2),0,16)
                    };
                }
                if (str[4]=='Y') {
                    return (Address){
                        ADDR_ZERO_PAGE_Y,
                        stoi(str.substr(1,2),0,16)
                    };
                }
                // If there's no X or Y, keep going to return an unknown address
            }
            if (IS_HEX_CHAR(str[3])) { // it's absolute not indexed!
                return (Address){
                    ADDR_ABSOLUTE,
                    stoi(str.substr(1,4),0,16)
                };
            }
        }
        
    }
    return (Address){
        ADDR_INVALID,
        -1
    };
}

Instruction Assembler::parseInstruction(std::string line) {
    std::smatch m;
    std::regex_match(line,m,instructionPattern);

    if (DEBUG) {
        printf("Parsing instruction: '%s'\n",line.c_str());
        int i=0;
        for (auto group : m) {
            printf("\tgroup %d: '%s'\n",i,group.str().c_str());
            i++;
        }
    }

    std::string mnemonic = m[1];
    Address addr;
    if (m[3]!="") {
        addr = parseAddress(m[3]);
        if (DEBUG) printf("\t(%d,%04x)\n",addr.addrMode,addr.location);
    }

    Instruction inst = (Instruction){mnemonic,addr};
    return inst;
}
