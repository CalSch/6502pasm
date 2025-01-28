# 6502pasm (WIP)
A portable 6502 assembler written in C++

## The Goal
I wanted to make a 6502 IDE for the M5Stack Cardputer (an ESP32 based computer), but I couldn't find an assembler that didn't rely on the underlying operating system (which the Cardputer doesn't have) so I'm making my own! I'm hoping to have a 6502 assembler contained in a single file (well, two files including the .h) while using minimal standard libraries (hopefully only stdio for sprintf, stdlib for malloc, and regex)
