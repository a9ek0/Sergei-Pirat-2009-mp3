#include "lyb/menu.h"

int main( ) {
    NODE *root = NULL;

    menu(&root);

    free_tree(root);
   return 0;
}

