# copy: ../src/6502pasm.*
# 	cp ../src/6502pasm.* .
main: main.cpp ../src/6502pasm.* demo.s
	g++ -o main ../src/6502pasm.cpp -I../src main.cpp
clean:
	rm -v 6502pasm.*
	rm -v main