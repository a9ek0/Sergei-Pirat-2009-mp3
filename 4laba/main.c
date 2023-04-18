#include <stdio.h>
#include <Windows.h>
#include "functions.h"
#include "lyb/menu.h"

int main(int argc, char *argv[]) {
    NODE *root = NULL;
    //// заменить статическое выделение памяти на динамическое
    menu(&root);

    free_tree(root);
    return 0;
}

