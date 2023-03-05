#include <stdlib.h>
#include <windows.h>
#include "mylib/structure.h"
#include "mylib/menu.h"

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    TV *tv;
    tv = (TV*) calloc(1, sizeof(TV));
    int size = 0;
    menu(tv, size);
    return 0;
}