#include <stdio.h>
#include "lyb/functions.h"
#include <Windows.h>

/// -

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    FILE *f;
    Stack *stack;
    stack = create_stack();

    char *word;
    word = (char*) malloc(100);

    fopen_s(&f, "rjomba.txt", "r");

    Node *new_node = NULL;
    new_node = (Node*)malloc(sizeof(Node));

    while(fscanf(f, "%s", word) == 1)
    {
        Data *data;
        data = (Data*) malloc(sizeof (Data));
        data->name = (char*) malloc(strlen(word) + 1);
        strcpy(data->name, word);
        data->frequency = 1;
        if(find_in_stack(stack, word) == 0)
        {
            push(stack, data);
        }
        else
        {
            find_node(stack, find_in_stack(stack, word), &new_node);
            new_node->data->frequency++;
        }
        free(word);
        word = (char*) malloc(100);
    }
    fclose(f);
    empty_the_stack(stack);
    return 0;
}
