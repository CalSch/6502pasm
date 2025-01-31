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

    printf("Output hex (%d bytes):\n",assembler.output.size());
    for (int i=0;i<assembler.output.size();i++) {
        if (i%8==0)
            printf("  ");
        printf("%02x ",assembler.output[i]);
        if (i%8==7)
            printf("\n");
    }
    printf("Labels (%d labels):\n",assembler.labels.size());
    for (Label l : assembler.labels) {
        printf("  %s @ 0x%04x\n",l.name.c_str(),l.address);
    }

    return 0;
}