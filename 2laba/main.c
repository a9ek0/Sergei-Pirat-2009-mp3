#include <stdio.h>
#include "lyb/functions.h"
#include <Windows.h>

/// -
void find_biggest_popular(Stack *stack);

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    Stack *stack;
    stack = create_stack();
    text_to_stack("rjomba.txt", stack);
    find_biggest_popular(stack);
    //empty_the_stack(stack);
    return 0;
}

void find_biggest_popular(Stack *stack)
{
    unsigned long long int size;
    size = stack_size(stack);
    Data *buff_data;
    buff_data = (Data*) malloc(sizeof (Data));
    buff_data->name = (char*) malloc(1);
    Stack *buff_stack;
    buff_stack = create_stack();
    Node *new_node = stack->top;
    for (int i = 0; i < size; ++i) {
            if(strlen(new_node->data->name) == BIG_WORD)
            {
                copy_data(buff_data, new_node->data);
                push(buff_stack, buff_data);
            }
            new_node = new_node->next;
    }
    empty_the_stack(buff_stack);
}
/////////find_biggest_popular(stack);
////////find_lowest_unpopular(stack);
////////find_in_file_and_swap(f, word);

