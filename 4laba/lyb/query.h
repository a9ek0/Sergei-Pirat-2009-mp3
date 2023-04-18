#ifndef INC_4LABA_QUERY_H
#define INC_4LABA_QUERY_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"
#include "check.h"
#include "tree.h"
#include "tree_srucutre.h"
#define MAX_LINE_LENGTH 1024

int ask_question(NODE **node, const char *answer);
char *add_extension(char *word, const char *extension);
void add_word_to_beginning(char *str, const char *word);
void replace_char(char *line, char old_char, char new_char);
void get_question_or_answer(char *input);
void get_input(char *input, const char *str1, const char *str2);
#endif //INC_4LABA_QUERY_H
