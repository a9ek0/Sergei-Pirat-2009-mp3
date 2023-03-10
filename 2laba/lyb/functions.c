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
    node->data = (Data*) malloc(sizeof (Data));
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
    if(is_empty(stack) == 1)
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

void empty_the_stack(Stack *stack)
{
    if(stack == NULL)
        exit(EXIT_FAILURE);
    int size = stack_size(stack);
    printf("%d ", size);
    for (int i = 0; i < size; ++i) {
        Data *data;
        data = pop(stack);
        printf("%d - ", data->frequency);
        printf("%s \n", data->name);
    }
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
    if (stack == NULL || *node == NULL)
    {
        printf("Invalid stack or node pointer\n");
        return;
    }

    Node *new_node = stack->top;
    for (int i = 0; i < num && new_node != NULL; i++)
    {
        new_node = new_node->next;
    }
    *node = new_node;
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
    if(dest_data == NULL || source_data == NULL)
        exit(EXIT_FAILURE);
    dest_data->name = (char*) malloc(strlen(source_data->name) + 1);
    strcpy(dest_data->name, source_data->name);
    dest_data->frequency = source_data->frequency;
}

void dell_punct_marks(char **word_ptr) {
    if (word_ptr == NULL || *word_ptr == NULL) {
        return;
    }
    char *word = *word_ptr;
    size_t size = strlen(word);
    while (ispunct(word[0])) {
        memmove(word, word + 1, size--);
    }
    while (size > 0 && ispunct(word[size - 1])) {
        word[--size] = '\0';
    }
    *word_ptr = word;
}
////////////////////////////FILES
void text_to_stack(char* name, Stack *stack)
{
    FILE *f;
    char *word;
    word = (char*) malloc(sizeof(char) * 50);
    fopen_s(&f, name, "r");
    Node *new_node = (Node*)malloc(sizeof(Node));  // выделение памяти для узла списка
    Data *data;
    while(fscanf(f, "%s", word) == 1)
    {
        data = (Data*) malloc(sizeof (Data));
        data->name = (char*) malloc(strlen(word) + 1);
        dell_punct_marks(&word);
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
        free(data);
        word = (char*) malloc(sizeof(char) * 50);
    }
    free(word);
    fclose(f);
}