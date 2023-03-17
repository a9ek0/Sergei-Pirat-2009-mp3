#include "functions.h"

////////////////////////STACK

Stack *create_stack()
{
    Stack *stack = (Stack*) malloc(sizeof (Stack));
    stack->top = NULL;
    return stack;
}
Node* create_node(Data* data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void push(Stack* stack, Data* data) {
    Node* new_node = create_node(data);
    new_node->next = stack->top;
    stack->top = new_node;
}

Data* pop(Stack* stack) {
    if (stack->top == NULL) {
        return NULL;
    }
    Data* data = stack->top->data;
    Node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
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
    Node *current_node = stack->top;
    while(current_node != NULL)
    {
        Node *next_node = current_node->next;
        free(current_node->data->name);
        free(current_node->data);
        free(current_node);
        current_node = next_node;
    }
    stack->top = NULL;
}

void rewrite_stack(char* new_file_name, Stack *stack)
{
    clear(stack);
    text_to_stack(new_file_name, stack);
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

void print_stack(Stack* stack) {
    printf("Stack contents:\n");
    Node* current_node = stack->top;
    while (current_node != NULL) {
        printf("\n%s - %d\n", current_node->data->name, current_node->data->frequency);
        current_node = current_node->next;
    }
}

void sort_stack(Stack *stack) {
    int n = stack_size(stack);
    Node *curr = stack->top;
    for (int i = 0; i < n; i++) {
        curr = stack->top;
        for (int j = 0; j < n - i - 1; j++) {
            if (strlen(curr->data->name) < strlen(curr->next->data->name)) {
                swap(curr, curr->next);
            }
            else if (strlen(curr->data->name) == strlen(curr->next->data->name) && curr->data->frequency < curr->next->data->frequency) {
                swap(curr, curr->next);
            }
            curr = curr->next;
        }
    }
}

void swap(Node *a, Node *b) {
    Data *temp = a->data;
    a->data = b->data;
    b->data = temp;
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


void find_popular(Stack *stack)
{
    unsigned long long int size;
    size = stack_size(stack);
    Data *buff_data;
    buff_data = (Data*) malloc(sizeof (Data));
    Node *new_node;
    for (int i = 0; i < size; ++i) {
        new_node = stack->top;
        for (int j = 0; j < size - 1; ++j) {
            if (new_node->data->frequency < new_node->next->data->frequency) {
                copy_data(buff_data, new_node->data);
                copy_data(new_node->data, new_node->next->data);
                copy_data(new_node->next->data, buff_data);
            }
            new_node = new_node->next;
        }
    }
    free(buff_data);
}


void find_unpopular(Stack *stack)
{
    unsigned long long int size;
    size = stack_size(stack);
    Data *buff_data;
    buff_data = (Data*) malloc(sizeof (Data));
    Node *new_node;
    for (int i = 0; i < size; ++i) {
        new_node = stack->top;
        for (int j = 0; j < size - 1; ++j) {
            if (new_node->data->frequency > new_node->next->data->frequency) {
                copy_data(buff_data, new_node->data);
                copy_data(new_node->data, new_node->next->data);
                copy_data(new_node->next->data, buff_data);
            }
            new_node = new_node->next;
        }
    }
    free(buff_data);
}

///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Data* push_specific_node(Stack *stack, int node)
{
    if(stack == NULL)
    {
        printf("Stack doesn't exist!");
        return NULL;
    }
    Stack *tmp_stack;
    tmp_stack = create_stack();
    Node *tmp_node;
    Data *tmp_data;
    for (int i = 0; i < node; ++i) {
        push(tmp_stack, pop(stack));
        tmp_node = stack->top->next;
    }
    tmp_data = pop(stack);
    for (int i = 0; i < node; ++i) {
        push(stack, pop(tmp_stack));
    }
    tmp_node = NULL;
    free(tmp_node);
    return tmp_data;
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
    dest_data->name[strlen(source_data->name) + 1] = '\0';
    dest_data->frequency = source_data->frequency;
}
char* dell_punct_marks(char *word_ptr) {
    if (word_ptr == NULL || *word_ptr == '\0') {
        return NULL;
    }
    char *word = word_ptr;
    size_t size = strlen(word);
    while (ispunct(word[0])) {
        memmove(word, word + 1, size--);
    }
    while (size > 0 && ispunct(word[size - 1])) {
        word[--size] = '\0';
    }

    return word;
}
/*void dell_punct_marks(char **word_ptr) {
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
}*/
////////////////////////////FILES
void text_to_stack(char* name, Stack *stack)
{
    FILE *f;
    char word[MAX_WORD_LEN];
    char *cleaned_word;
    f = fopen( name, "r");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    Node *new_node = (Node*)malloc(sizeof(Node));
    Data *data;
    while(fscanf(f, "%s", word) == 1)
    {
        data = (Data*) malloc(sizeof (Data));
        cleaned_word = dell_punct_marks(word);
        data->name = (char*) malloc(strlen(word) + 1);
        strcpy(data->name, cleaned_word);
        data->frequency = 1;
        if(find_in_stack(stack, cleaned_word) == 0)
        {
            push(stack, data);
        }
        else
        {
            find_node(stack, find_in_stack(stack, cleaned_word), &new_node);
            new_node->data->frequency++;
        }
    }
        //free(data);
    fclose(f);
}

void copy_file(const char *source_filename, const char *destination_filename) {
    FILE *source_file;
    FILE *destination_file;
    char buffer[1024];
    size_t bytes_read;

    source_file = fopen(source_filename, "rb");
    destination_file = fopen(destination_filename, "wb");

    if (source_file == NULL || destination_file == NULL) {
        printf("Ошибка: не удалось открыть файлы для копирования\n");
        return;
    }

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
        fwrite(buffer, 1, bytes_read, destination_file);
    }

    fclose(source_file);
    fclose(destination_file);
}

void replace_word(char* text, const char* old_word, const char* new_word) {
    char* pos = text;
    int old_len = strlen(old_word);
    int new_len = strlen(new_word);

    while ((pos = strstr(pos, old_word)) != NULL) {
        // Заменяем найденное вхождение old_word на new_word
        memmove(pos + new_len, pos + old_len, strlen(pos + old_len) + 1);
        memcpy(pos, new_word, new_len);
        pos += new_len;
    }
}

void shift_file(FILE *file, int shift)
{
    int pos = ftell(file);
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, pos, SEEK_SET);
    char *buff = (char*) malloc((size + 1) * sizeof (char));
    fread(buff, size, 1, file);
    buff[size] = '\0';
    fseek(file, pos + shift, SEEK_SET);
    fputs(buff, file);
    free(buff);
    int fd = fileno(file);
    off_t new_size = lseek(fd, 0, SEEK_CUR) - shift;
    ftruncate(fd, new_size);
}