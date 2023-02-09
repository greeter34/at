all:
	gcc -g *.c -o test -Wall -lcurses
	x86_64-w64-mingw32-gcc *.c -o test.exe -lcurses -l:libgcc_eh.a  -l:libstdc++.a

linux:
	gcc -g *.c -o test -Wall -lcurses

windows:
	x86_64-w64-mingw32-gcc *.c -o test.exe -lcurses --static

clean:
	rm *.o *.exe test
