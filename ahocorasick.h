/*
 * Utilities for Aho-Corasick algorithm
 * A keyword tree with failure links is represented as an array of node structs,
 * each containing a character, next nodes, parent node, failure links and outputs.
 * buildtree() allocates and builds a keyword tree from a string of patterns separated by a space.
 * search() threads through a given string using the given nodetree, and prints each match to stdout
 * printnode() and freenode() are auxiliary utilities for keyword tree;
 * printnode() displays the fields of the node as given in the sample output,
 * and freenode() frees the dynamically allocated arrays in each node.
 * To free a nodetree, simply iterating through the array and freeing each member is fine.
 */

#ifndef __AHOCORASICK_H
#define __AHOCORASICK_H

#include <stdlib.h>

struct node {
	char c; // may also be \0 for the root node
	int *next, nextlen; // needs to be freed
	int parent, fail, depth; // link to parent and failure states, depth in tree
	char **outputs; // list of strings, needs to be freed but individual strings do not (taken directly from patterns)
	int outlen;     // really no need for it to be a list, but that's what the prompt says
};

// tree represented as array
typedef struct node *nodetree;

// reads patterns from string, length of array fixed as e.g. strlen(patterns), will need to be freed
// spaces in patterns will be replaced with \0 after scanning, each node will point to those substrings
// returns length of tree in len
nodetree buildtree(char *patterns, int *len);

// search patterns in text, print results
void search(nodetree tree, char *text);

// return index of child of tree[i] with character c; tree[i].nextlen if no child found
int findchild(nodetree tree, int i, char c);

// print build tree to file
void printtree(FILE *file, nodetree tree, int len);

void printnode(FILE *file, struct node *node);

void freetree(nodetree tree, int len);

void freenode(struct node *node);

#endif
