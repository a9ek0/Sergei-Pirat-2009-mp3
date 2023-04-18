#include "functions.h"















char* first_number_from_string(const char* string) {
    char* number = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
    int i = 0;
    while (string[i] != ' ' && string[i] != '\n' && string[i] != '\0') {
        number[i] = string[i];
        i++;
    }
    if (i != 0) {
        number[i] = '\0';
        return number;
    } else {
        free(number);
        return NULL;
    }
}










