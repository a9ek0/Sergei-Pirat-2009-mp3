#include <stdio.h>
#include "lyb/functions.h"
#include <Windows.h>

#define MAX_WORD_LEN 50 // максимальная длина слова
/// -
void find_in_file(char *file_name, char *word);
void switch_word_in_file(char *file_name, char *word, int position);
void find_in_file_big(char *file_name, char *small_word, char *big_word);
void find_in_file_small(char *file_name, char *small_word, char *big_word);
void replace_word(const char* file_name, const char* old_word, const char* new_word);
void replace_words_in_file(char *file_name, FILE *lyb, char *first_word, char *second_word);
int check_in_lyb(FILE *lyb, char *word);

int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    char *big_word;
    char *small_word;
    big_word = (char*) malloc(MAX_WORD_LEN * sizeof (char));
    small_word = (char*) malloc(MAX_WORD_LEN * sizeof (char));

    Stack *stack;
    stack = create_stack();
    text_to_stack("rjomba.txt", stack);

    FILE *lyb;
    if (fopen_s(&lyb, "lyb.txt", "w+t") != 0) {
        printf("Failed to open lyb file.\n");
        return 0;
    }
    fclose(lyb);
    for (int i = 0; i < 10; ++i) {

        if (fopen_s(&lyb, "lyb.txt", "a+t") != 0) {
            printf("Failed to open lyb file.\n");
            return 0;
        }

        find_smallest(stack, small_word);
        fputs(small_word, lyb);
        fputs(" ", lyb);

        find_biggest(stack, big_word);
        fputs(big_word, lyb);
        fputs("\n", lyb);

        replace_words_in_file("rjomba.txt", lyb, small_word, big_word);
        rewrite_stack("compressed_file.txt", stack);

        fclose(lyb);
    }
    free(big_word);
    free(small_word);
    return 0;
}


////////find_in_file_and_swap(f, word);

int check_in_lyb(FILE *lyb, char *word)
{
    char *word_tmp;
    word_tmp = (char*) malloc(MAX_WORD_LEN * sizeof (char));
    rewind(lyb);
    while(fscanf(lyb, "%s", word_tmp) == 1)
    {
        if(strcmp(word, word_tmp) == 0)
        {
            free(word_tmp);
            return 1;
        }
    }
    free(word_tmp);
    return 0;
}

void replace_words_in_file(char *file_name, FILE *lyb, char *first_word, char *second_word) {
    FILE *f;
    FILE *compressed_file;
    char *word_tmp;
    char *cleaned_word;
    word_tmp = (char*) malloc(50 * sizeof (char));
    if (fopen_s(&f, file_name, "r+t") != 0) {
        printf("Failed to open input file.\n");
        return;
    }
    if (fopen_s(&compressed_file, "compressed_file.txt", "r+t") != 0) {
        printf("Failed to create output file.\n");
        fclose(f);
        return;
    }
    while(fscanf(f, "%s", word_tmp) == 1) {
        cleaned_word = dell_punct_marks(word_tmp);
        //printf("%s ", cleaned_word);
        if (strcmp(first_word, cleaned_word) == 0) {
            fputs(second_word, compressed_file);
            fputs(" ", compressed_file);
        } else if (strcmp(second_word, cleaned_word) == 0) {
            fputs(first_word, compressed_file);
            fputs(" ", compressed_file);
        } else if(check_in_lyb(lyb, cleaned_word) == 0){
            fputs(word_tmp, compressed_file);
            fputs(" ", compressed_file);
        }
    }
    free(word_tmp);
    fclose(compressed_file);
    fclose(f);
}

