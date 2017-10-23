/*
 * CS 481
 * Ata Deniz Aydin
 * 21502637
 *
 * Definitions and auxiliary functions for keyword trees
 * A keyword tree with failure links is represented as an array of node structs,
 * each containing a character, next nodes, parent node, failure links and outputs.
 * - printtree() outputs a depth-first traversal of the build tree into a file.
 * - freetree() frees each dynamically allocated resource in the tree, including the tree itself.
 * - printnode() and freenode() are auxiliary functions called by printtree() and freetree().
 */

#ifndef __KEYTREE_H
#define __KEYTREE_H

#include <stdio.h>

struct node {
	char c; // may also be \0 for the root node
	int *next, nextlen; // needs to be freed
	int parent, fail, depth; // link to parent and failure states, depth in tree
	char **outputs; // list of strings, needs to be freed but individual strings do not (taken directly from patterns)
	int outlen;     // no need for it to be a list, but that's what the prompt asks
};

// tree represented as array
typedef struct node *keytree;

// print build tree to file
void printtree(FILE *file, keytree tree, int len);

void printnode(FILE *file, struct node *node);

void freetree(keytree tree, int len);

void freenode(struct node *node);

#endif
