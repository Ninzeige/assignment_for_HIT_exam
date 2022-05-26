all: main

main: src/main.c student wins
	gcc -o main src/main.c student.o wins.o -lncursesw -Iinclude

student: src/student.c
	gcc -c -o student.o src/student.c -lncursesw -Iinclude

wins: src/wins.c
	gcc -c -o wins.o src/wins.c -lncursesw -Iinclude