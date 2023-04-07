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
    data = create_data(NULL, NULL, NULL);
    root = create_node(&data);

    return 0;
}

DATA *create_data(const char *question, const char *answer_yes, const char *answer_no)
{
    DATA *data;
    strcpy(data->answer_no, answer_no);
    strcpy(data->answer_yes, answer_yes);
    strcpy(data->question, question);
    return data;
}

NODE *create_node(DATA **data)
{
    if(*data == NULL )
        exit(EXIT_FAILURE);
    NODE *node;
    node->data = *data;
    node->left = NULL;
    node->right = NULL;
}

