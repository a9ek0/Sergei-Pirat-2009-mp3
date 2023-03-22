#include "lyb/functions.h"


int main() {

    Stack *stack;
    stack = create_stack();

    Library *lyb = malloc(sizeof(Library));
    initialize_lyb(lyb);

    text_to_stack("rjomba.txt", stack);
    stack_to_lyb(stack, lyb);
    for (int i = 0; i < lyb->num_of_words; ++i) {
        printf("\n%s - %s", lyb->words[i].word1, lyb->words[i].word2);
    }

    compress_file("rjomba.txt", "compressed_file.txt", lyb);

    put_lyb_to_file("compressed_file.txt", lyb);

    free_lyb(lyb);
    return 0;
}