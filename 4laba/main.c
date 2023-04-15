#include <stdio.h>
#include <Windows.h>
#define EMPTY_QUESTION '\0'
#define MAX_LINE_LENGTH 1024


LRESULT WindowProc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if(msg == WM_DESTROY){
        PostQuitMessage(0);
    }else
        return DefWindowProcA(hWnd, msg, wParam, lParam);
}

typedef struct {
    char *question;
    char *answer;
} DATA;

typedef struct Node {
    DATA *data;
    struct Node *yes_branch;
    struct Node *no_branch;
} NODE;

DATA *create_data(const char *question, const char *answer);
NODE *create_node(DATA *data);
void check_answer(char *answer);
int ask_question(NODE **node, const char *answer);
void run_through_tree(NODE **root);
void rebase_tree(NODE **node);
void print_tree(NODE *root, int depth);
void tree_to_file(NODE *root, FILE *file, int depth);

char *first_number_from_string(const char *string);

void file_to_tree(NODE **root, FILE *file, int depth);

void add_node(NODE *parent, NODE *node, char direction);
void free_data(DATA *data);


int main() {
    NODE *root = NULL;
    DATA *data;
    FILE *tree_data;
    int extension = 1;

    tree_data = fopen("tree_data.txt", "rt");

    if(tree_data == NULL)
    {
        fprintf(stderr, "File doesn't exist!");
        exit(EXIT_FAILURE);
    }

    file_to_tree(&root, tree_data, 0);

    ///tut slovov mojno chtobi polzovatel vvodil
    //data = create_data(NULL , "123");
    //root = create_node(data);
    while(extension) {
        print_tree(root, 0);
        run_through_tree(&root);
        printf("Do you want to continue?\n");
        scanf_s("%d", &extension);
    }
    printf("Do you want to save this tree?\n");
    scanf_s("%d", &extension);
    if(!extension)
    {
        free(root);
        free(data);
        fclose(tree_data);
        return 0;
    }else{
        tree_to_file(root, tree_data, 0);
    }
    free(data);
    free(root);
    fclose(tree_data);
    return 0;
}

void run_through_tree(NODE **root)
{
    NODE *tmp = *root;

    char answer[4];

    int expression = 0;

        while (expression != 1) {

            if(tmp->data->question == NULL)
            {
                printf("It's %s\n", tmp->data->answer);
                rebase_tree(&tmp);
                return;
            }

            printf("%s\n", tmp->data->question);
            fflush(stdin);

            check_answer(answer);
            expression = ask_question(&tmp, answer);

        }

        printf("It's %s!\n", strcmp("Yes", answer) == 0 ? tmp->yes_branch->data->answer : tmp->no_branch->data->answer);

        rebase_tree(strcmp("Yes", answer) == 0 ? &tmp->yes_branch : &tmp->no_branch);
}

int ask_question(NODE **node, const char *answer)
{
    if((*node)->yes_branch->yes_branch == NULL && (*node)->no_branch->no_branch == NULL)
    {
        return 1;
    }
    if (strcmp("Yes", answer) == 0) {
        *node = (*node)->yes_branch;
    }else if (strcmp("No", answer) == 0) {
        *node = (*node)->no_branch;
    }
    return 0;
}

void rebase_tree(NODE **node)
{
    char answer[4];
    char new_question[256];
    char correct_answer[256];
    DATA *data;

    printf("I'm right?\n");
    check_answer(answer);

    if (strcmp("Yes", answer) == 0)
    {
        printf("Ura!!!\n");
    }
    else
    {
        printf("A kto eto bil?\n");
        fflush(stdin);
        gets(correct_answer);

        printf("A 4e kak otlichit'?\n");
        fflush(stdin);
        gets(new_question);

        DATA *yes_data = create_data(NULL , correct_answer);
        NODE *yes_node = create_node(yes_data);
     //   free(yes_data);

        DATA *no_data = create_data(NULL , (*node)->data->answer);
        NODE *no_node = create_node(no_data);
      //  free(no_data);

        NODE* tmp = *node;
        tmp->yes_branch = yes_node;
        tmp->no_branch = no_node;

        tmp->data->question = malloc(strlen(new_question) + 1);
        strcpy(tmp->data->question, new_question);

        char *new_answer = malloc(strlen(tmp->data->answer) + 1);
        strcpy(new_answer, tmp->data->answer);
        tmp->data->answer = new_answer;
    }
}

void check_answer(char *answer)
{
    scanf_s("%s", answer);
    while(strcmp(answer, "Yes") != 0 && strcmp(answer, "No") != 0) {
        printf("Wrong input!\n");
        fflush(stdin);
        scanf_s("%s", answer);
    }
}

DATA *create_data(const char *question, const char *answer)
{
    DATA *data = malloc(sizeof(DATA));
    if (!data) {
        return NULL;
    }
    data->question = NULL;
    data->answer = NULL;

    if (question) {
        data->question = malloc(strlen(question) + 1);
        if (!data->question) {
            free(data);
            return NULL;
        }
        strcpy(data->question, question);
    }

    if (answer) {
        data->answer = malloc(strlen(answer) + 1);
        if (!data->answer) {
            free(data->question);
            free(data);
            return NULL;
        }
        strcpy(data->answer, answer);
    }

    return data;
}

void print_tree(NODE *root, int depth) {
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    if (root->data->question != NULL) {
        printf("Question: %s\n", root->data->question);
    } else {
        printf("Answer: %s\n", root->data->answer);
    }

    print_tree(root->yes_branch, depth + 1);
    print_tree(root->no_branch, depth + 1);
}

void tree_to_file(NODE *root, FILE *file, int depth)
{
    if (root == NULL) {
        return;
    }

    if (root->data->question != NULL) {
        fprintf(file, "%d", depth);
        fputs(" Q ", file);
        fputs(root->data->question, file);
        fputs("\n", file);
    } else {
        fprintf(file, "%d", depth);
        fputs(" A ", file);
        fputs(root->data->answer, file);
        fputs("\n", file);
    }

    tree_to_file(root->yes_branch, file, depth + 1);
    tree_to_file(root->no_branch, file, depth + 1);
}

NODE *create_node(DATA *data) {
    NODE *node = (NODE *) malloc(sizeof(NODE));
    node->data = data;
    node->yes_branch = NULL;
    node->no_branch = NULL;
    return node;
}

char* first_number_from_string(const char* string) {
    char* number = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
    int i = 0;
    while (string[i] != ' ' && string[i] != '\n' && string[i] != '\0') {
        number[i] = string[i];
        i++;
    }
    if (i != 0) {
        number[i] = '\0';
        return number;
    } else {
        free(number);
        return NULL;
    }
}

void add_node(NODE *parent, NODE *node, char direction) {
    if (direction == 'Y') {
        parent->yes_branch = node;
    } else {
        parent->no_branch = node;
    }
}

void free_data(DATA *data) {
    if (data->question != NULL) {
        free(data->question);
    }
    if (data->answer != NULL) {
        free(data->answer);
    }
    free(data);
}

void free_tree(NODE *node) {
    if (node->yes_branch != NULL) {
        free_tree(node->yes_branch);
    }
    if (node->no_branch != NULL) {
        free_tree(node->no_branch);
    }
    free_data(node->data);
    free(node);
}




///////хачи это правильно
void file_to_tree(NODE **root, FILE *file, int depth)
{
    char *number;
    char line[MAX_LINE_LENGTH];

    if (root == NULL || file == NULL) {
        return;
    }

    if(fgets(line, MAX_LINE_LENGTH, file) == NULL)
    {
        return;
    }

    line[strcspn(line, "\n")] = '\0';

    number = first_number_from_string(line);
    if (number == NULL) {
        return;
    }

    NODE *node = malloc(sizeof(NODE));
    node->data = malloc(sizeof(DATA));

    if (line[strlen(number) + 1] == 'Q') {
        DATA *data = node->data;
        data->question = strdup(line + strlen(number) + 3);
        data->answer = NULL;
    node->yes_branch = NULL;
    node->no_branch = NULL;
    *root = node;

    file_to_tree(&((*root)->yes_branch), file, depth + 1);
    file_to_tree(&((*root)->no_branch), file, depth + 1);
    } else {
        DATA *data = node->data;
        data->answer = strdup(line + strlen(number) + 3);
        data->question = NULL;
        node->yes_branch = NULL;
        node->no_branch = NULL;
        *root = node;
    }

    free(number);
}