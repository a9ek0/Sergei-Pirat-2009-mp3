#ifndef INC_4LABA_MEMORY_H
#define INC_4LABA_MEMORY_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "tree_srucutre.h"
#define MAX_LINE_LENGTH 1024

void free_tree(NODE *root);
void free_data(DATA *data);
DATA *create_data(const char *question, const char *answer);
NODE *create_node(DATA *data);
void add_node(NODE *parent, NODE *node, char direction);
#endif //INC_4LABA_MEMORY_H
