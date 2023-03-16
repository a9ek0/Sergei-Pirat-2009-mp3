#include "functions.h"

////////////////////////STACK

char* least_frequent_word(Stack* stack, int length) {
    // Создаем пустой словарь
    Data* dict = malloc(sizeof(Data) * 10);
    int dict_size = 10;

    // Перебираем все слова в стеке
    Node* current = stack->top;
    while (current != NULL) {
        // Если длина слова не соответствует заданной, пропускаем его
        if (strlen(current->data->name) != length) {
            current = current->next;
            continue;
        }

        // Ищем слово в словаре
        int index = -1;
        for (int i = 0; i < dict_size; i++) {
            if (dict[i].name == NULL) {
                index = i;
                break;
            }
            if (strcmp(dict[i].name, current->data->name) == 0) {
                index = i;
                break;
            }
        }

        // Если слово уже есть в словаре, увеличиваем его частоту
        if (index != -1) {
            dict[index].frequency++;
        }
            // Иначе, добавляем его в словарь
        else {
            if (dict_size == 0) {
                dict = realloc(dict, sizeof(Data));
            } else {
                dict = realloc(dict, sizeof(Data) * dict_size * 2);
            }
            dict[dict_size].name = current->data->name;
            dict[dict_size].frequency = 1;
            dict_size++;
        }

        current = current->next;
    }

    // Находим самое редкое слово в словаре
    int min_freq = INT_MAX;
    char* least_frequent = NULL;
    for (int i = 0; i < dict_size; i++) {
        if (dict[i].name != NULL && dict[i].frequency < min_freq) {
            min_freq = dict[i].frequency;
            least_frequent = dict[i].name;
        }
    }

    // Освобождаем память
    free(dict);

    return least_frequent;
}



void qwe(Stack *stack)
{
    Stack *tmp_stack;
    tmp_stack = create_stack();
    unsigned long long size;
    size = stack_size(stack);
    for (int i = 0; i < size; ++i) {

    }
}





char* most_frequent_word(Stack *stack, int length) {
    // Сначала создаем пустой словарь
    Data *dict = malloc(sizeof(Data) * 10);
    int dict_size = 10;

    // Перебираем все слова в стеке
    Node *current = stack->top;
    while (current != NULL) {
        // Если длина слова не соответствует заданной, пропускаем его
        if (strlen(current->data->name) != length) {
            current = current->next;
            continue;
        }

        // Ищем слово в словаре
        int index = -1;
        for (int i = 0; i < dict_size; i++) {
            if (dict[i].name == NULL) {
                index = i;
                break;
            }
            if (strcmp(dict[i].name, current->data->name) == 0) {
                index = i;
                break;
            }
        }

        // Если слово уже есть в словаре, увеличиваем его частоту
        if (index != -1) {
            dict[index].frequency++;
        }
            // Иначе, добавляем его в словарь
        else {
            if (dict_size == 0) {
                dict = realloc(dict, sizeof(Data));
            } else {
                dict = realloc(dict, sizeof(Data) * dict_size * 2);
            }
            dict[dict_size].name = current->data->name;
            dict[dict_size].frequency = 1;
            dict_size++;
        }

        current = current->next;
    }

    // Находим самое частое слово в словаре
    int max_freq = 0;
    char *most_frequent = NULL;
    for (int i = 0; i < dict_size; i++) {
        if (dict[i].name != NULL && dict[i].frequency > max_freq) {
            max_freq = dict[i].frequency;
            most_frequent = dict[i].name;
        }
    }

    // Освобождаем память
    free(dict);

    return most_frequent;
}

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

void empty_the_stack(Stack *stack)
{
    if(stack == NULL)
        exit(EXIT_FAILURE);
    int size = stack_size(stack);
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
    char *word;
    word = (char*) malloc(sizeof(char) * 50);
    fopen_s(&f, name, "r");
    Node *new_node = (Node*)malloc(sizeof(Node));
    Data *data;
    while(fscanf(f, "%s", word) == 1)
    {
        data = (Data*) malloc(sizeof (Data));
        data->name = (char*) malloc(strlen(word) + 1);
        word = dell_punct_marks(word);
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