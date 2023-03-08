#include <stdio.h>
#include "lyb/functions.h"
#include <Windows.h>

/// -
int find_in_stack(Stack *stack, char* word);
void find_node(Stack *stack, int num, Node **node);

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    FILE *f;
    Stack *stack;
    stack = create_stack();

    char *word;
    word = (char*) malloc(100);

    fopen_s(&f, "rjomba.txt", "r");

    Node *new_node;
    new_node = (Node*)malloc(sizeof(Node));
    Data *data;
    data = (Data*) malloc(sizeof (Data));
    data->name = (char*) malloc(1);
    while(fscanf(f, "%s", word) == 1)
    {
        strcpy(data->name, word);
        data->frequency = 1;
        if(find_in_stack(stack, word) == 0)
        {
            push(stack, data);
            //printf("%s\n ", word);
        }
        else
        {
            find_node(stack, find_in_stack(stack, word), &new_node);
            new_node->data->frequency++;
        }
        //free(word);
        word = (char*) malloc(100);
    }
    free(word);
    fclose(f);
    for (int i = 0; i < stack_size(stack); ++i) {
        data = pop(stack);
        printf("%d - ", data->frequency);
        printf("%s \n", data->name);
    }
    return 0;
}

int find_in_stack(Stack *stack, char* word)
{
    if(stack == NULL)
        exit(EXIT_FAILURE);
    Node *new_node = stack->top;
    int size = stack_size(stack);
    for (int i = 0; i < size; ++i) {
        if(strcmp(word, new_node->data->name) == 0)
            return i;
        new_node = new_node->next;
    }
    return 0;
}

void find_node(Stack *stack, int num, Node **node)
{
    if(stack == NULL)
        exit(EXIT_FAILURE);
    Node *new_node = stack->top;
    for (int i = 0; i < num + 1; ++i) {
        new_node = new_node->next;
    }
    *node = new_node;
}
