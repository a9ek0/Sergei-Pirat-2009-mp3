#ifndef INC_2LABA_FUNCTIONS_H
#define INC_2LABA_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <ctype.h>

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


enum word_length{
    BIG_WORD = 5,
    SMALL_WORD = 3
};

typedef struct Data{
    char *name;
    int frequency;
}Data;

typedef struct Node{
    struct Data *data;
    struct Node *next;
}Node;

typedef struct Stack{
    struct Node *top;
}Stack;



void compress_file(const char *input_file, const char* output_file, const Library *lyb);


//////////////////////////////STACK
char* most_frequent_word(Stack *stack, int length);
char* least_frequent_word(Stack* stack, int length);

///////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Data* push_specific_node(Stack *stack, int node);


Stack *create_stack();
void push(Stack *stack, Data *data);
Data *pop(Stack *stack);
Data *peek(const Stack *stack);
int is_empty(const Stack *stack);
int stack_size(Stack *stack);
void clear(Stack *stack);
void destroy(Stack *stack);
int find_in_stack(Stack *stack, const char *word);
void find_node(Stack *stack, int num, Node **node);
void empty_the_stack(Stack *stack);
void find_biggest(Stack *stack, char *word);
void find_smallest(Stack *stack, char *word);
void find_popular(Stack *stack);
void find_unpopular(Stack *stack);
void rewrite_stack(const char *new_file_name, Stack *stack);


void swap(Node *a, Node *b);
void sort_stack_h_l(Stack* stack);
void sort_stack_l_h(Stack *stack);
void print_stack(Stack* stack);

void stack_to_lyb(Stack *stack, Library *lyb);

//////////////////////////////MEMORY
void free_node(Node *node);

/////////////////////////////HUI_Z
void copy_data(Data *dest_data, const Data *source_data);
char* dell_punct_marks(char *word_ptr);
void replace_word(char* text, const char* old_word, const char* new_word);


////////////////////////////FILES
void text_to_stack(const char *name, Stack *stack);
void copy_file(const char *source_filename, const char *destination_filename);
void shift_file(FILE *file, int shift);
void free_lyb(Library *lyb);
void save_control_characters(FILE *file, FILE *file1);
int my_isalpha(int ch);
void initialize_lyb(Library *lyb);
void put_lyb_to_file(const char *file_name, const Library *lyb);
void check_control_chars(FILE* input_file, FILE* output_file);
#endif //INC_2LABA_FUNCTIONS_H
