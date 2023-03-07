#include "functions.h"

////////////////////////STACK
Stack *create_stack()
{
    Stack *stack = (Stack*) malloc(sizeof (Stack));
    stack->top = NULL;
    return stack;
}

void push(Stack *stack, Data *data)
{
    Node *node = (Node*) malloc(sizeof(Node));
    copy_data(node->data, data);
    node->next = stack->top;
    stack->top = node;
}

Data *pop(Stack *stack)
{
    if(stack->top == NULL)
    {
        printf("Stack is empty");
        exit(EXIT_FAILURE);
    }
    Node *top_node = stack->top;
    Data *data = (Data*) malloc(sizeof (Data));
    copy_data(data, top_node->data);
    stack->top = top_node->next;
    free_node(top_node);
    return data;
}

Data *peek(Stack *stack)
{
    if(stack->top == NULL)
    {
        printf("Stack is empty");
        exit(EXIT_FAILURE);
    }
    Node *top_node = stack->top;
    Data *data = (Data*) malloc(sizeof (Data));
    copy_data(data, top_node->data);
    return data;
}

int is_empty(Stack *stack)
{
    if(stack->top == NULL)
        return 1;
    else
        return 0;
}

int stack_size(Stack *stack)
{
    int size = 0;
    if(is_empty(stack) == 0)
        return 0;
    Node *new_stack = stack->top;
    while(new_stack != NULL)
    {
        size++;
        new_stack = new_stack->next;
    }
    return size;
}

void clear(Stack *stack)
{
    const void *tmp;
    if(is_empty(stack) == 0)
        exit(EXIT_FAILURE);
    Node *new_stack = stack->top;
    while(new_stack != NULL)
    {
        free(new_stack->data->name);
        tmp = new_stack->next;
        free(new_stack);
        new_stack = tmp;
        tmp = NULL;
    }
}

void destroy(Stack *stack)
{
    const void *tmp;
    if(is_empty(stack) == 0 || stack == NULL)
        exit(EXIT_FAILURE);
    Node *new_stack = stack->top;
    while(new_stack != NULL)
    {
        free(new_stack->data->name);
        tmp = new_stack->next;
        free(new_stack);
        new_stack = tmp;
        tmp = NULL;
    }
    free(stack);
}
///////////////////////////////////////MEMORY
void free_node(Node *node)
{
    if(node == NULL)
        exit(EXIT_FAILURE);
    free(node->data->name);
    free(node);
}


///////////////////////////////////////HUI Z
void copy_data(Data *dest_data, Data *source_data)
{
    dest_data = (Data*) malloc(sizeof (source_data));
    dest_data->name = (char*) malloc(strlen(source_data->name) + 1);
    strcpy(dest_data->name, source_data->name);
    dest_data->length = source_data->length;
}


////////////////////////////FILES