all: main

main: src/main.c student wins
	gcc -o main src/main.c student.o wins.o controls.o -lncursesw -Iinclude

student: src/student.c
	gcc -c -o student.o src/student.c -lncursesw -Iinclude

wins: src/wins.c controls include/wins.h
	gcc -c -o wins.o src/wins.c -lncursesw -Iinclude 

controls: src/controls.c include/controls.h
	gcc -c -o controls.o src/controls.c -lncursesw -Iinclude