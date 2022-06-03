all: main

main: src/main.c student wins interface operation
	x86_64-w64-mingw32-gcc -o main src/main.c student.o wins.o controls.o operation.o interface.o -I/usr/x86_64-w64-mingw32/include/ncursesw -Iinclude -lformw -lncursesw

student: src/student.c
	x86_64-w64-mingw32-gcc -c -o student.o src/student.c -I/usr/x86_64-w64-mingw32/include/ncursesw -Iinclude

wins: src/wins.c include/wins.h controls
	x86_64-w64-mingw32-gcc -c -o wins.o src/wins.c -I/usr/x86_64-w64-mingw32/include/ncursesw -Iinclude -lform -lncursesw

controls: src/controls.c include/controls.h
	x86_64-w64-mingw32-gcc -c -o controls.o src/controls.c -I/usr/x86_64-w64-mingw32/include/ncursesw -Iinclude -lncursesw

interface: src/interface.c include/interface.h
	x86_64-w64-mingw32-gcc -c -o interface.o src/interface.c -I/usr/x86_64-w64-mingw32/include/ncursesw -Iinclude -lncursesw
operation: src/operation.c include/operation.h
	x86_64-w64-mingw32-gcc -c -o operation.o src/operation.c -Iinclude -lncursesw -I/usr/x86_64-w64-mingw32/include/ncursesw 

clean:
	rm -r *.o

