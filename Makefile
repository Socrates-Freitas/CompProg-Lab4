compile:
	gcc Main.c -c -m32 -fno-PIC -Wall -o Main.o
	gcc -c Parser.c -m32 -fno-PIC -Wall -o Parser.o
	gcc Main.o Parser.o -m32 -fno-PIC -o Main

debug:
	gcc -g Main.c Parser.c -m32 -fno-PIC -Wall -o Main

run:
	./Main