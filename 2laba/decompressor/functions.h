#ifndef DECOMPRESSOR_FUNCTIONS_H
#define DECOMPRESSOR_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX_WORD_LEN 50
typedef unsigned long long ull;

typedef struct{
    char *word1;
    char *word2;
}replacement_words;

typedef struct{
    replacement_words *words;
    int num_of_words;
}Library;

char* dell_punct_marks(char *word_ptr);
void find_key(FILE *file, const char *key);
void replace_word(char* text, const char* old_word, const char* new_word);
void save_control_characters(FILE* file, FILE* file1);
void decompress_file(const char *input_file, const char* output_file, const Library *lyb);
void delete_in_file_lyb(const char *file_name, const char *key);
void file_to_lyb(FILE *file, Library *lyb, const char *key);
void free_lyb(Library *lyb);
void initialize_lyb(Library *lyb);

#endif //DECOMPRESSOR_FUNCTIONS_H
