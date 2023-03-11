#include <stdio.h>
#include "lyb/functions.h"
#include <Windows.h>
#define MAX_WORD_LEN 50 // максимальная длина слова
/// -
void find_in_file(char *file_name, char *word);
void switch_word_in_file(char *file_name, char *word, int position);
void find_in_file_big(char *file_name, char *small_word, char *big_word);
void find_in_file_small(char *file_name, char *small_word, char *big_word);
void replace_word(const char* file_name, const char* old_word, const char* new_word);
int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    char *big_word;
    char *small_word;
    big_word = (char*) malloc(sizeof (char));
    small_word = (char*) malloc(sizeof (char));
    Stack *stack;
    stack = create_stack();
    text_to_stack("rjomba.txt", stack);
    for (int i = 0; i < 10; ++i) {
        find_smallest(stack, small_word);
        printf("%s ", small_word);
        find_biggest(stack, big_word);
        printf("%s ", big_word);
        //replace_word("rjba.txt", small_word, big_word);
        //replace_word("rjba.txt", big_word, small_word);

        //find_in_file_big("rjba.txt", small_word, big_word);
        //find_in_file_small("rjba.txt", small_word, big_word);
    }//empty_the_stack(stack);
    return 0;
}

////////find_in_file_and_swap(f, word);

void find_in_file_small(char *file_name, char *small_word, char *big_word)
{
    FILE *f;
    char *word_tmp;
    word_tmp = (char*) malloc(50 * sizeof (char));
    fopen_s(&f, file_name, "r");
    while(fscanf(f, "%s", word_tmp) == 1)
    {
        dell_punct_marks(&word_tmp);
        if(strcmp(small_word, word_tmp) == 0)
        {
            switch_word_in_file(file_name, big_word, -strlen(word_tmp));
        }
    }
    free(word_tmp);
}

void find_in_file_big(char *file_name, char *small_word, char *big_word)
{
    FILE *f;
    char *word_tmp;
    word_tmp = (char*) malloc(50 * sizeof (char));
    fopen_s(&f, file_name, "r");
    while(fscanf(f, "%s", word_tmp) == 1)
    {
        dell_punct_marks(&word_tmp);
        if(strcmp(big_word, word_tmp) == 0)
        {
            switch_word_in_file(file_name, small_word, -strlen(word_tmp));
        }
    }
    free(word_tmp);
}

void switch_word_in_file(char *file_name, char *word, int position)
{
    FILE *f;
    fopen_s(&f, file_name, "rt+");
    fseek(f, position, SEEK_SET);
    fputs(word, f);
}


void replace_word(const char* file_name, const char* old_word, const char* new_word) {
    FILE* file = fopen(file_name, "r+"); // открытие файла для чтения и записи
    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
        return;
    }

    char word[MAX_WORD_LEN + 1]; // буфер для хранения слова
    char c;
    int i = 0;
    while ((c = fgetc(file)) != EOF) { // читаем файл символ за символом
        if (isalnum(c) || c == '_') { // если символ является буквой, цифрой или знаком подчеркивания, добавляем его в слово
            word[i++] = c;
        }
        else { // если символ не является буквой, цифрой или знаком подчеркивания, это конец слова
            word[i] = '\0';
            i = 0;
            if (strcmp(word, old_word) == 0 && (isspace(c) || ispunct(c) || c == EOF)) { // если слово совпадает с искомым словом и после него идет пробел, знак препинания или конец файла
                fseek(file, -strlen(old_word), SEEK_CUR); // перемещаем указатель на начало слова
                fputs(new_word, file); // записываем новое слово
            }
        }
    }

    fclose(file); // закрываем файл
}