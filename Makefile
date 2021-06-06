compile:
	gcc  -c Main.c -m32 -fno-PIC -Wall -o Main.o
	gcc -c Parser.c -m32 -fno-PIC -Wall -o Parser.o
	gcc -c Builtin.c -m32 -fno-PIC -Wall -o Builtin.o
	gcc Main.o Parser.o Builtin.o -m32 -fno-PIC -o Main

debug:
	gcc -g Main.c Parser.c Builtin.c -m32 -fno-PIC -Wall -o Main

run:
	./Main