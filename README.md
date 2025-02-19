# 6502pasm (WIP)
A portable 6502 assembler written in C++

## The Goal
I wanted to make a 6502 IDE for the M5Stack Cardputer (an ESP32 based computer), but I couldn't find an assembler that didn't rely on the underlying operating system (which the Cardputer doesn't have) so I'm making my own! I'm hoping to have a 6502 assembler contained in a single file (well, two files including the .h) while using minimal standard libraries (hopefully only stdio for sprintf, stdlib for malloc, and regex)

## Todo
- Not-so-critical
  - Auto-allocate variables
  - Math expressions (probably RPN)
  - Errors
  - Expand syntax
    - Decimal and binary numbers
    - Instruction and label on the same line
    - Make label colon optional
  - Maybe use a namespace
  - Update docs

## Usage
To test:
- Clone the repo
- Go to `test/`
- run `make main`
- run `./main`
To use in your own project: (DON'T DO IT YET, THIS ISN'T FINISHED)
- Clone the repo
- Copy `src/6502pasm.h` and `src/6502pasm.cpp` into your project
- Success!
- If not success, please leave an issue, as I'm trying to make it as easy as possible to integrate

## Docs (also WIP)
### `Assembler()` class
This is the class that contains the assembler. It has:
- `std::vector<std::string> input_lines`: A list of lines, each line has only one thing:
  - a directive (ex. `.org $0800`)
  - a label (ex. `cool_label:`)
  - or an instruction (ex. `lda #$05`)
  - Lines can also have a comment (everything after a `;` is ignored)
- `std::vector<unsigned char> output_bytes`: A list of bytes as the assembled code
- `std::vector<Label> labels`: A list of labels that were found
- `std::vector<Macro> macros`: A list of macros that were found
- `int assemble()`: Assembles the `input_lines` into the `output_bytes`. Returns 0 if successful, 1 if not.

## Example
```cpp
#include "6502pasm.h"

int main() {
  Assembler assembler = Assembler();

  // Loads some simple stuff into input_lines
  assembler.input_lines.push_back(std::string(".org $0800"));
  assembler.input_lines.push_back(std::string(".macro addr $05"));
  assembler.input_lines.push_back(std::string("main:"));
  assembler.input_lines.push_back(std::string(" lda #$2e ; comment"));
  assembler.input_lines.push_back(std::string(" LDX $04 ; capital mnemonic"));
  assembler.input_lines.push_back(std::string(" ldy %addr ; macro"));
  assembler.input_lines.push_back(std::string(" jmp main ; uses a label"));

  // Assemble it
  assembler.assemble();

  // Output it
  printf("Output hex (%d bytes):\n",assembler.output_bytes.size());
  for (int i=0;i<assembler.output_bytes.size();i++) {
    if (i%8==0)
      printf("  %02x: ",i);
    printf("%02x ",assembler.output_bytes[i]);
    if (i%8==7)
      printf("\n");
  }
  printf("\n");
  printf("Labels (%d labels):\n",assembler.labels.size());
  for (Label l : assembler.labels) {
    printf("  %s @ 0x%04x\n",l.name.c_str(),l.location);
  }
  printf("Macros (%d macros):\n",assembler.macros.size());
  for (Macro m : assembler.macros) {
    printf("  %s = '%s'\n",m.name.c_str(),m.text.c_str());
  }

  return 0;
}
```
You can also look at [test/main.cpp](https://github.com/CalSch/6502pasm/blob/master/test/main.cpp)