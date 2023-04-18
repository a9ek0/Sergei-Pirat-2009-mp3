#include "check.h"

void check_answer(char *answer)
{
    scanf_s("%s", answer);
    while(strcmp(answer, "Yes") != 0 && strcmp(answer, "No") != 0) {
        printf("Wrong input!\n");
        fflush(stdin);
        scanf_s("%s", answer);
    }
}

int check_input(const char *input, const char *str1, const char *str2) {
    int match1 = strcmp(input, str1);
    int match2 = strcmp(input, str2);
    if (match1 == 0 || match2 == 0) {
        return 1;
    } else {
        return 0;
    }
}

int is_in_file(FILE *file, const char *word)
{
    char line[MAX_LINE_LENGTH];
    fseek(file, 0, SEEK_SET);

    while(fgets(line, MAX_LINE_LENGTH, file) != NULL)
    {
        if(strcmp(word, line) == 0)
        {
            return 1;
        }
    }
    return 0;
}
