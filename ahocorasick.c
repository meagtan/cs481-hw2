/*
 * CS 481
 * Ata Deniz Aydin
 * 21502637
 *
 * Implementation of the Aho-Corasick algorithm.
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ahocorasick.h"

// increment size of dynamic array
// arguments shouldn't need to be parenthesized
// no need for calloc and null check for array, realloc behaves like malloc if argument null
#define EXPANDARR(arr, len, maxlen, type) do {			\
	++len;							\
	if (!arr) arr = calloc(maxlen, sizeof(type));		\
	else if (len >= maxlen) {				\
		maxlen <<= 1;					\
		arr = realloc(arr, sizeof(type) * maxlen);	\
	}							\
} while (0)

keytree buildtree(char *patterns, int *len)
{
	keytree tree = calloc(strlen(patterns)+1, sizeof(struct node));
	int i = 0,      // current index of tree
	    maxlen = 4; // maximum length of next array, applies to all nodes, doubled when necessary
	char *word = patterns; // start of current word
	int j;

	// root of tree set to '\0' automatically
	// add each word to tree sequentially
	*len = 1;
	for (char *c = patterns; *c; ++c) {
		*c = tolower(*c); // just in case
		if (isalpha(*c)) { // extend current word
			// look for child with character c
			j = findchild(tree, i, *c);

			// if found, set i to the state found
			// else set tree[len] to current character, add len to children of tree[i], set i to len and increment len
			if (j < tree[i].nextlen) {
				tree[tree[i].next[j]].parent = i;
				i = tree[i].next[j];
			} else {
				// extend size of tree[i].next dynamically, set its last element to tree[len++]
				EXPANDARR(tree[i].next, tree[i].nextlen, maxlen, int);
				tree[i].next[j] = *len;
				tree[*len].c = *c;
				tree[*len].parent = i;
				tree[*len].depth = tree[i].depth + 1;
				i = *len;
				++*len;
			}
		} else {
			// finish word by setting *c to \0, add word to tree[i].output, set word to c+1
			*c = '\0';
			EXPANDARR(tree[i].outputs, tree[i].outlen, maxlen, char *);
			tree[i].outputs[tree[i].outlen-1] = word; // assuming only one space exists; otherwise will set output of root
			word = c+1;
			i = 0; // go back to root for new word
		}
	}

	// construct failure links using BFS

	// know number of elements, implement queue in array
	// since elements are inserted into the queue in exactly the BFS order and only once,
	// the queue does not need to wrap around and will at the end contain each index in BFS order
	int *queue = calloc(*len, sizeof(int));
	int child, fail;
	queue[0] = 0; // start from root
	for (i = 0, j = 1; i < j; ++i) { // j represents end of queue, queue[i] node currently visited
		// add children of queue[i] to queue
		for (int k = 0; k < tree[queue[i]].nextlen; ++k)
			queue[j++] = tree[queue[i]].next[k];

		// visit queue[i], traverse fail states of parent until root reached or match found
		// may be another auxiliary function
		fail  = tree[queue[i]].parent;
		child = findchild(tree, fail, tree[queue[i]].c);
		while (fail) {
			fail  = tree[fail].fail;
			child = findchild(tree, fail, tree[queue[i]].c);
			if (child < tree[fail].nextlen) {
				tree[queue[i]].fail = tree[fail].next[child];
				break;
			}
		}
		// tree[queue[i]].fail = fail;
	}
	free(queue);

	return tree;
}

void search(FILE *f, keytree tree, char *text)
{
	int i = 0, j; // current and next state

	fprintf(f, "Search\n----------------------------------------------------------------------\n");

	// iterate through string
	for (int k = 0; text[k]; ++k) {
		// look for child with character *c
		j = findchild(tree, i, text[k]);

		// if found, update state
		// else search from the failure link, until you reach the root
		while (i && j >= tree[i].nextlen) {
			i = tree[i].fail;
			j = findchild(tree, i, text[k]);
		}

		// change state if found, otherwise stay at root
		if (j < tree[i].nextlen)
			i = tree[i].next[j];

		// print outputs associated to node, assuming "" is not an output
		for (j = 0; j < tree[i].outlen; ++j)
			fprintf(f, "keyword: %s index: %d\n", tree[i].outputs[j], k - tree[i].depth + 1); // tree[i].depth gives length of match, k last character
	}
}

int findchild(keytree tree, int i, char c)
{
	int j;
	// iterate through next states for tree[i]
	for (j = 0; j < tree[i].nextlen; ++j)
		if (tree[tree[i].next[j]].c == tolower(c)) // lowercase just in case
			return j;
	return j;
}
