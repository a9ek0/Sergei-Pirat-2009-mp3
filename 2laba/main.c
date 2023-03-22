#include "lyb/functions.h"


int main() {
    char input_file[11] = "rjomba.txt";
    char output_file[20] = "compressed_file.txt";
    Stack *stack;
    stack = create_stack();

    Library *lyb = malloc(sizeof(Library));
    initialize_lyb(lyb);

    text_to_stack(input_file, stack);

    stack_to_lyb(stack, lyb);

    compress_file(input_file, output_file, lyb);

    put_lyb_to_file(output_file, lyb);

    free_lyb(lyb);
    return 0;
}