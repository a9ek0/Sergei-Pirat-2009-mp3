#ifndef INC_4LABA_CHECK_H
#define INC_4LABA_CHECK_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"
#include "tree_srucutre.h"
#define MAX_LINE_LENGTH 1024

void check_answer(char *answer);
int check_input(const char *input, const char *str1, const char *str2);
int is_in_file(FILE *file, const char *word);
#endif //INC_4LABA_CHECK_H
