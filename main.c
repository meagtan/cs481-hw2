#include <stdio.h>
#include <stdlib.h>

#include "ahocorasick.h"

#define INPUT  "input.txt"
#define OUTPUT "output.txt"

#define MAXCHAR 1024

int main(void)
{
	char *patterns, *text;
	nodetree tree;
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

	// output build tree
	printtree(stdout, tree, len);

	freetree(tree, len);
	free(patterns);
	free(text);
}
