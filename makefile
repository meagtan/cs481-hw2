main: main.c ahocorasick.c
	gcc -O3 -o main main.c ahocorasick.c keytree.c

clean:
	rm -f ./main output.txt
