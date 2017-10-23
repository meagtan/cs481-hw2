/*
 * CS 481
 * Ata Deniz Aydin
 * 21502637
 *
 * I/O interface for the Aho-Corasick algorithm, as implemented in ahocorasick.c.
 * The constants INPUT and OUTPUT define the filenames of the input and output files.
 * The main function reads the patterns and text from the input into strings,
 * constructs a keyword tree from the patterns, and threads through text using the keyword tree.
 */

#include <stdio.h>
#include <stdlib.h>

#include "ahocorasick.h"

#define INPUT  "input.txt"
#define OUTPUT "output.txt"

// size of string buffers read from file
#define MAXCHAR 4096

int main(void)
{
	char *patterns, *text;
	keytree tree;
	int len;
	FILE *fin, *fout;

	// read input file
	fin = fopen(INPUT, "r");
	if (!fin) {
		fprintf(stderr, "Error: input file %s does not exist.\n", INPUT);
		return 1;
	}

	// read patterns from first line, text from second line
	patterns = malloc(MAXCHAR * sizeof(char));
	fgets(patterns, MAXCHAR, fin);

	text = malloc(MAXCHAR * sizeof(char));
	fgets(text, MAXCHAR, fin);

	fclose(fin);

	// build tree from patterns
	tree = buildtree(patterns, &len);

	// write to output file
	fout = fopen(OUTPUT, "w");
	if (!fout) {
		fprintf(stderr, "Error: could not open output file %s.\n", OUTPUT);
		return 1;
	}

	// output build tree
	printtree(fout, tree, len);

	fprintf(fout, "\n");

	// search, output result
	search(fout, tree, text);

	fclose(fout);

	freetree(tree, len);
	free(patterns);
	free(text);
}
