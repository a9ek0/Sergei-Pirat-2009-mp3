#ifndef INC_2LABA_FUNCTIONS_H
#define INC_2LABA_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_WORD_LEN 50
#define MAX_LIB_WORDS 100

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

//////////////////////////////STACK
char* most_frequent_word(Stack *stack, int length);
char* least_frequent_word(Stack* stack, int length);

///////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Data* push_specific_node(Stack *stack, int node);


Stack *create_stack();
void push(Stack *stack, Data *data);
Data *pop(Stack *stack);
Data *peek(Stack *stack);
int is_empty(Stack *stack);
int stack_size(Stack *stack);
void clear(Stack *stack);
void destroy(Stack *stack);
int find_in_stack(Stack *stack, char* word);
void find_node(Stack *stack, int num, Node **node);
void empty_the_stack(Stack *stack);
void find_biggest(Stack *stack, char *word);
void find_smallest(Stack *stack, char *word);
void find_popular(Stack *stack);
void find_unpopular(Stack *stack);
void rewrite_stack(char* new_file_name, Stack *stack);

void swap(Node *a, Node *b);
void sort_stack_h_l(Stack* stack);
void sort_stack_l_h(Stack *stack);
void print_stack(Stack* stack);

void stack_to_lyb(Stack *stack, Library *lyb);

//////////////////////////////MEMORY
void free_node(Node *node);

/////////////////////////////HUI_Z
void copy_data(Data *dest_data, Data *source_data);
char* dell_punct_marks(char *word_ptr);
void replace_word(char* text, const char* old_word, const char* new_word);


////////////////////////////FILES
void text_to_stack(char* name, Stack *stack);
void copy_file(const char *source_filename, const char *destination_filename);
void shift_file(FILE *file, int shift);
void free_lyb(Library *lyb);
void save_control_characters(FILE *file, FILE *file1);
int my_isalpha(int ch);
#endif //INC_2LABA_FUNCTIONS_H
