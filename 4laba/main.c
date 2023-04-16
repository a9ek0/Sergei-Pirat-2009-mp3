#include <stdio.h>
#include <Windows.h>
#include "functions.h"

LRESULT WindowProc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if(msg == WM_DESTROY){
        PostQuitMessage(0);
    }else
        return DefWindowProcA(hWnd, msg, wParam, lParam);
}

int main(int argc, char *argv[]) {

    //проверить надо будет ввод в дерево, а то какая-то хуйня

    NODE *root = NULL;
    DATA *data;
    data = create_data(NULL, "Pudge");
    root = create_node(data);
    menu(&root);

    free_data(data);
    free(root);

    return 0;
}

