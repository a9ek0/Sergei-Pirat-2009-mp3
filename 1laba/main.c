#include "structure.h"
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "Rus");
    int x = 0;
    struct film const *da;
    menu(da, x);
    return 0;
}

