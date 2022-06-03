all: main test_case

main: src/main.c student wins interface operation
	gcc -o main src/main.c student.o wins.o controls.o operation.o interface.o -lncursesw -Iinclude -lform

student: src/student.c
	gcc -c -o student.o src/student.c -lncursesw -Iinclude

wins: src/wins.c include/wins.h controls
	gcc -c -o wins.o src/wins.c -lncursesw -Iinclude -lform

controls: src/controls.c include/controls.h
	gcc -c -o controls.o src/controls.c -lncursesw -Iinclude

interface: src/interface.c include/interface.h
	gcc -c -o interface.o src/interface.c -lncursesw -Iinclude

operation: src/operation.c include/operation.h
	gcc -c -o operation.o src/operation.c -Iinclude

clean:
	rm -r *.o

