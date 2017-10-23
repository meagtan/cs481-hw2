/*
 * CS 481
 * Ata Deniz Aydin
 * 21502637
 *
 * Utilities for Aho-Corasick algorithm
 * - buildtree() allocates and builds a keyword tree from a string of patterns separated by a space.
 * - search() threads through a given string using the given keytree, and prints each match to file.
 * - findchild() is an auxiliary function used by both other functions, which looks for a child of
 *   the i'th node in the tree, accessed as tree[i], that matches the character c.
 */

#ifndef __AHOCORASICK_H
#define __AHOCORASICK_H

#include "keytree.h"

// reads patterns from string, length of array fixed as e.g. strlen(patterns), will need to be freed
// spaces in patterns will be replaced with \0 after scanning, each node will point to those substrings
// e.g. one string "carrot cool parrot\n\0" becomes three strings "carrot\0cool\0parrot\0\0",
// so that words would not have to be copied into other strings ('\n' comes from fgets)
// returns length of tree in len
keytree buildtree(char *patterns, int *len);

// search patterns in text, print results
void search(FILE *f, keytree tree, char *text);

// return index of child of tree[i] in tree[i].next with character c; tree[i].nextlen if no child found
int findchild(keytree tree, int i, char c);

#endif
