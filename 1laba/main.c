#include <stdlib.h>
#include <Windows.h>
#include "mylib/structure.h"
#include "mylib/menu.h"

int main() {
    FILE *f;
    f = fopen("qwe","r");
    fclose(f);
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    TV *tv;
    tv = (TV*) calloc(1, sizeof(TV));
    int size = 0;
    menu(tv, size);
    return 0;
}