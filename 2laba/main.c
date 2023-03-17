#include "lyb/functions.h"
#include <Windows.h>




int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Stack *stack;
    stack = create_stack();

    copy_file("rjomba.txt", "compressed_file.txt");

    //char text[100] = " shaking,";


    text_to_stack("rjomba.txt", stack);

    sort_stack(stack);

    print_stack(stack);

    //replace_word(text, "shaking", "get");

    return 0;
}

