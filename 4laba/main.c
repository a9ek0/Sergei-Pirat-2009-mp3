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

    /* NODE *root = NULL;

    menu(&root, "tree_data.txt");

    free(root);*/

    return 0;
}

