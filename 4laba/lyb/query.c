#include "query.h"

int ask_question(NODE **node, const char *answer)
{
    if((*node)->yes_branch->yes_branch == NULL && (*node)->no_branch->no_branch == NULL)
    {
        return 1;
    }
    if (strcmp("Yes", answer) == 0) {
        *node = (*node)->yes_branch;
    }else if (strcmp("No", answer) == 0) {
        *node = (*node)->no_branch;
    }
    return 0;
}

char *add_extension(char *word, const char *extension)
{
    word[strcspn(word, "\n")] = '\0';
    strcat(word, extension);
    return word;
}

void add_word_to_beginning(char *str, const char *word)
{
    size_t word_length = strlen(word);
    size_t str_length = strlen(str);
    memmove(str + word_length, str, str_length + 1);
    memcpy(str, word, word_length);
}

void replace_char(char *line, char old_char, char new_char)
{
    size_t length = strlen(line);
    for (int i = 0; i < length; i++) {
        if (line[i] == old_char) {
            line[i] = new_char;
        }
    }
}

void get_question_or_answer(char *input){
    while(strcmp(input, "\n\0") == 0)
    {
        printf("Wrong input!\n");
        fflush(stdin);
        fgets(input, MAX_LINE_LENGTH, stdin);
    }
}

void get_input(char *input, const char *str1, const char *str2) {
    while (!check_input(input, str1, str2)) {
        printf("Wrong input!\n");
        fflush(stdin);
        fgets(input, MAX_LINE_LENGTH, stdin);
    }
}
