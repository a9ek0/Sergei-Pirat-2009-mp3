#ifndef INC_2LABA_FUNCTIONS_H
#define INC_2LABA_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <ctype.h>

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


//////////////////////////////MEMORY
void free_node(Node *node);

/////////////////////////////HUI_Z
void copy_data(Data *dest_data, Data *source_data);
char* dell_punct_marks(char *word_ptr);

////////////////////////////FILES
void text_to_stack(char* name, Stack *stack);

#endif //INC_2LABA_FUNCTIONS_H
