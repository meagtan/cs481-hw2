/*
 * CS 481
 * Ata Deniz Aydin
 * 21502637
 *
 * Implementation of functions declared in keytree.h.
 */

#include <stdlib.h>

#include "keytree.h"

void printtree(FILE *f, keytree tree, int len)
{
	// header, then print each node
	fprintf(f, "Build tree\n----------------------------------------------------------------------\n");
	for (int i = 0; i < len; ++i)
		printnode(f, tree+i);
}

void printnode(FILE *f, struct node *node)
{
	// format: "char: c next states: [next] fail state: fail output: [outputs]\n"
	fprintf(f, "char: %c next states: [", node->c);
	for (int i = 0; i < node->nextlen; ++i)
		fprintf(f, "%s%d", i ? ", " : "", node->next[i]);
	fprintf(f, "] fail state: %d output: [", node->fail);
	for (int i = 0; i < node->outlen; ++i)
		fprintf(f, "%s'%s'", i ? ", " : "", node->outputs[i]);
	fprintf(f, "]\n");
}

void freetree(keytree tree, int len)
{
	// free each element, then free array
	while (--len) freenode(tree+len);
	free(tree);
}

void freenode(struct node *node)
{
	// does nothing if next or outputs is NULL
	free(node->next);
	free(node->outputs);
}
