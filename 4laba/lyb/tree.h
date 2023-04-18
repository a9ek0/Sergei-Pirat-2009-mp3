#ifndef INC_4LABA_TREE_H
#define INC_4LABA_TREE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "query.h"
#include "memory.h"
#include "tree_srucutre.h"
#define MAX_LINE_LENGTH 1024

void run_through_tree(NODE **root, FILE *log_file);
void print_tree(NODE *root, int depth);
void rebase_tree(NODE **node, FILE *log_file);
void tree_to_file(NODE *root, FILE *file, int depth);
void file_to_tree(NODE **root, FILE *file, int depth);
void manual_tree_filling(NODE **root, FILE *log_file);
char *choose_game();
#endif //INC_4LABA_TREE_H
