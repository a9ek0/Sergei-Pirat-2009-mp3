#ifndef INC_4LABA_FUNCTIONS_H
#define INC_4LABA_FUNCTIONS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE_LENGTH 1024
#define MAX_INPUT_LENGTH 10
typedef struct {
    char *question;
    char *answer;
} DATA;

typedef struct Node {
    DATA *data;
    struct Node *yes_branch;
    struct Node *no_branch;
} NODE;

DATA *create_data(const char *question, const char *answer);
NODE *create_node(DATA *data);
void check_answer(char *answer);
int ask_question(NODE **node, const char *answer);
void run_through_tree(NODE **root);
void rebase_tree(NODE **node);
void print_tree(NODE *root, int depth);
void tree_to_file(NODE *root, FILE *file, int depth);

char *first_number_from_string(const char *string);

void file_to_tree(NODE **root, FILE *file, int depth);

void add_node(NODE *parent, NODE *node, char direction);
void free_data(DATA *data);

void menu(NODE **root);

char *choose_game();
int is_in_file(FILE *file, const char *word);

char *add_extension(char *word, const char *extension);

void manual_tree_filling(NODE **root);
#endif //INC_4LABA_FUNCTIONS_H
