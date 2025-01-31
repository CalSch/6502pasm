#include <stdio.h>
#include "6502pasm.h"

int main() {
    Assembler assembler = Assembler();
    std::string currentLine("");
    FILE* infile = fopen("demo.s","r");
    char c;
    while ((c = fgetc(infile)) != EOF) {
        if (c=='\n') {
            assembler.input_lines.push_back(currentLine);
            currentLine = std::string("");
        } else {
            currentLine.push_back(c);
        }
    }

    assembler.assemble();

    return 0;
}