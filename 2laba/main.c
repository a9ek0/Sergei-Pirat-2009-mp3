#include <stdio.h>
#include "lyb/functions.h"
#include <Windows.h>

/// -


int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    Stack *stack;
    stack = create_stack();
    text_to_stack("rjomba.txt", stack);
    empty_the_stack(stack);
    return 0;
}

/////////find_biggest_popular(stack);
////////find_lowest_unpopular(stack);
////////find_in_file_and_swap(f, word);

