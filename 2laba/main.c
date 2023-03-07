#include <stdio.h>
#include "lyb/functions.h"
#include <Windows.h>

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    FILE *f;
    char *word;
    unsigned long long int n = 0;
    word = (char*) malloc(100);
    fopen_s(&f, "rjomba.txt", "r");
    while(fscanf(f, "%s", word) == 1)
    {
        n = strlen(word);
        if(n % 2 != 0)
        {
            word[n - 1] = '\0';
        }
        if((sizeof (word[0]) != 2 && sizeof(word[n]) != 2) || (word[0] == '«' && word[n] == '»'))
        {
            word[0] = ' ';
            word[n - 1] = '\0';
        }
        printf("%s ", word);
        free(word);
        word = (char*) malloc(100);
    }
    free(word);
    fclose(f);
    return 0;
}

