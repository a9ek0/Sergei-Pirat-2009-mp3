#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "structure.h"

int main() {
    TV *tv;
    int size = 0;
    create_struct_arr(&tv, &size);
    initiate_struct(tv, size);
    print_struct(tv, size);
    return 0;
}
