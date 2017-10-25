main: main.c ahocorasick.c
	gcc -O3 -o main main.c ahocorasick.c keytree.c

clear:
	rm -f ./main output.txt
