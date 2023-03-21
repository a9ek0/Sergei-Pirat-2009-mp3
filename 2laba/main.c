#include "lyb/functions.h"
#include <Windows.h>


int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Stack *stack;
    stack = create_stack();

    Library *lyb = malloc(sizeof(Library));
    initialize_lyb(lyb);

    text_to_stack("rjomba.txt", stack);
    stack_to_lyb(stack, lyb);

    compress_file("rjomba.txt", "compressed_file.txt", lyb);

    put_lyb_to_file("compressed_file.txt", lyb);

    free_lyb(lyb);
    return 0;
}