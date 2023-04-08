#include <stdio.h>
#include <Windows.h>

LRESULT WindowProc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if(msg == WM_DESTROY){
        PostQuitMessage(0);
    }else
        return DefWindowProcA(hWnd, msg, wParam, lParam);
}

typedef struct {
    char *question;
    char *answer_yes;
    char *answer_no;
} DATA;

typedef struct Node{
    DATA *data;
    struct Node *left;
    struct Node *right;
} NODE;

DATA *create_data(const char *question, const char *answer_yes, const char *answer_no);
NODE *create_node(DATA **data);


int main() {
    NODE *root;
    DATA *data;
    data = create_data("It's alive?", "Pudge", "Ilyas");
    root = create_node(&data);
    printf("%s", root->data->question);
    free(root);
    free(data);
    return 0;
}

DATA *create_data(const char *question, const char *answer_yes, const char *answer_no)
{
    DATA *data = malloc(sizeof(DATA));
    if (!data) {
        return NULL; // failed to allocate memory, return NULL
    }
    data->question = malloc(strlen(question) + 1);
    if (!data->question) {
        free(data);
        return NULL; // failed to allocate memory, return NULL
    }
    data->answer_yes = malloc(strlen(answer_yes) + 1);
    if (!data->answer_yes) {
        free(data->question);
        free(data);
        return NULL; // failed to allocate memory, return NULL
    }
    data->answer_no = malloc(strlen(answer_no) + 1);
    if (!data->answer_no) {
        free(data->answer_yes);
        free(data->question);
        free(data);
        return NULL; // failed to allocate memory, return NULL
    }
    strcpy(data->question, question);
    strcpy(data->answer_yes, answer_yes);
    strcpy(data->answer_no, answer_no);
    return data;
}

NODE *create_node(DATA **data)
{
    if(*data == NULL )
        exit(EXIT_FAILURE);
    NODE *node = malloc(sizeof(NODE));
    if (!node) {
        return NULL;
    }
    node->data = *data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

