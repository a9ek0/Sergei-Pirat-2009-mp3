#include <stdio.h>
#include "lyb/functions.h"
#include <Windows.h>
#include <unistd.h>
#define MAX_WORD_LEN 50 // максимальная длина слова

#define MAX_LENGTH 1000

/// -
#define MAX_LINE_LENGTH 1000
#define MAX_WORD_LENGTH 100

void replace_words(const char *name, const char *word1, const char *word2);

void shift_file(FILE *file, int shift);
int sign_account(const char *word);

int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    copy_file("rjomba.txt", "compressed_file.txt");

    replace_words("compressed_file.txt", "shaking", "get");

    /*FILE * f;
    f = fopen("compressed_file.txt", "rt+");

    int i = 0;

    fclose(f);
*/

    return 0;
}

///////////////Буфер
///////////////Поиск слова
///////////////Удаление знаков препинания
///////////////Сравнение
///////////////Перенос текста в лево или право
///////////////Запись слова





void shift_file(FILE *file, int shift)
{
    int pos = ftell(file);
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, pos, SEEK_SET);
    char *buff = (char*) malloc((size + 1) * sizeof (char));
    fread(buff, size, 1, file);
    buff[size] = '\0';
    fseek(file, pos + shift, SEEK_SET);
    fputs(buff, file);
    free(buff);
    int fd = fileno(file);
    off_t new_size = lseek(fd, 0, SEEK_CUR) - shift;
    ftruncate(fd, new_size);
}



void replace_words(const char *name, const char *word1, const char *word2)
{
    FILE *file;
    file = fopen(name, "rt+");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    int offset;
    unsigned long long int shift;
    unsigned long long pos;
    char word_tmp[MAX_WORD_LEN];
    char *cleaned_word;
    while(fscanf(file, "%s", word_tmp) == 1)
    {
        //fseek(file, pos, SEEK_SET);
        cleaned_word = dell_punct_marks(word_tmp);
        if (strcmp(cleaned_word, word1) == 0)
        {
            //offset = sign_account(word_tmp);
            //printf("%d", offset);
            //fseek(file, 20, SEEK_SET);
            shift = (strlen(word1) - strlen(word2));
            shift_file(file, -(int)shift);
            pos = ftell(file);
            fseek(file, pos - strlen(word2), SEEK_SET);
            fprintf(file, "%s", word2);
            fseek(file, 0, SEEK_CUR);
        }
        else if(strcmp(cleaned_word, word2) == 0)
        {
            //offset = sign_account(word_tmp);
            //pos = ftell(file);
            //fseek(file, pos + offset, SEEK_SET);
            //shift = (strlen(word2) - strlen(word1));
            //shift_file(file, (int)shift);
            //fputs(word1, file);
            //fseek(file, pos, SEEK_SET);
        }else
            continue;
//        free(cleaned_word);
    }
    fclose(file);
}

int sign_account(const char *word)
{
    unsigned long long word_size;
    int sign = 0;
    int flag = 0;
    word_size = strlen(word);
    for (int i = 0; i < word_size; ++i) {
        if(!isalnum(word[i]) && flag == 0)
            sign++;
        else
            flag = 1;
        if(!isalnum(word[i]) && flag == 1)
            sign--;
    }
    word_size -= sign;
    return (int)word_size;
}





/*
void replace_words(char *name, char *word1, char *word2)
{
    FILE *file;
    file = fopen(name, "r+t");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    char buffer[1024];
    size_t word1_len = strlen(word1);
    size_t word2_len = strlen(word2);
    while (fgets(buffer, 1024, file))
    {

        char *p = strstr(buffer, word2);
        while (p != NULL) {
            strncpy(p, word1, strlen(word1));
            p = strstr(p + strlen(word1), word2);
        }

        */
/* char *p = buffer;
         while ((p = strstr(p, word1)) != NULL)
         {
             memcpy(p, word2, word2_len);
             p += word2_len;
             memmove(p, p + word1_len, strlen(p + word1_len) + 1);
         }

         p = buffer;
         while ((p = strstr(p, word2)) != NULL)
         {
             memcpy(p, word1, word1_len);
             p += word1_len;
             memmove(p, p + word2_len, strlen(p + word2_len) + 1);
         }*//*


        printf("%s", buffer);
    }

    fclose(file);
}
*/




/*
void replace_words(const char *filename, const char *word1, const char *word2)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    char buffer[1024];
    size_t word1_len = strlen(word1);
    size_t word2_len = strlen(word2);

    while (fgets(buffer, 1024, file))
    {
        char *p = buffer;
        while ((p = strstr(p, word1)) != NULL)
        {
            memcpy(p, word2, word2_len);
            p += word2_len;
            memmove(p, p + word1_len, strlen(p + word1_len) + 1);
        }

        p = buffer;
        while ((p = strstr(p, word2)) != NULL)
        {
            memcpy(p, word1, word1_len);
            p += word1_len;
            memmove(p, p + word2_len, strlen(p + word2_len) + 1);
        }

        printf("%s", buffer);
    }

    fclose(file);
}
*/
/*
void replace_words_in_file(const char* filename, const char* word1, const char* word2) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char buffer[1000];
    size_t word1_len = strlen(word1);
    size_t word2_len = strlen(word2);

    FILE* temp_file = tmpfile();
    if (temp_file == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        char* pos = buffer;
        while ((pos = strstr(pos, word1)) != NULL) {
            fwrite(buffer, 1, pos - buffer, temp_file);
            fwrite(word2, 1, word2_len, temp_file);
            pos += word1_len;
            buffer[strlen(buffer) - strlen(pos)] = '\0';
            fputs(pos, temp_file);
        }

        pos = buffer;
        while ((pos = strstr(pos, word2)) != NULL) {
            fwrite(buffer, 1, pos - buffer, temp_file);
            fwrite(word1, 1, word1_len, temp_file);
            pos += word2_len;
            buffer[strlen(buffer) - strlen(pos)] = '\0';
            fputs(pos, temp_file);
        }
    }

    fclose(file);

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        fclose(temp_file);
        return;
    }

    rewind(temp_file);

    while (fgets(buffer, sizeof(buffer), temp_file)) {
        fputs(buffer, file);
    }

    fclose(file);
    fclose(temp_file);
}
*/


/*
void replace_words_in_file(char *file_name, char *first_word, char *second_word) {
    FILE *f;
    char *word_tmp;
    char *cleaned_word;
    word_tmp = (char*) malloc(50 * sizeof (char));
    if (fopen_s(&f, file_name, "r+t") != 0) {
        printf("Failed to open input file.\n");
        return;
    }
    while(fscanf(f, "%s", word_tmp) == 1) {
        cleaned_word = dell_punct_marks(word_tmp);
        //printf("%s ", cleaned_word);
        if (strcmp(first_word, cleaned_word) == 0) {
            fseek(f, 2, SEEK_SET);
            fputs(second_word, f);
        } else if (strcmp(second_word, cleaned_word) == 0) {
            fseek(f, 0, SEEK_SET);
            fputs(first_word, f);
        }
    }
    free(word_tmp);
    fclose(f);
}
*/


/*void replace_word(char *filename, char *word1, char *word2) {
    FILE *fp = fopen(filename, "r+");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int word1_len = strlen(word1);
    int word2_len = strlen(word2);
    int max_word_len = (word1_len > word2_len) ? word1_len : word2_len;
    char *temp = (char*)malloc((max_word_len + 1) * sizeof(char));  // allocate memory for temp buffer

    // replace all occurrences of word1 with word2 and vice versa
    while (fscanf(fp, "%s", temp) == 1) {
        if (strcmp(temp, word1) == 0) {
            fseek(fp, -word1_len, SEEK_CUR);
            fprintf(fp, "%s", word2);
            if (word2_len < word1_len) {
                int i;
                for (i = 0; i < word1_len - word2_len; i++) {
                    fprintf(fp, " ");
                }
            }
        } else if (strcmp(temp, word2) == 0) {
            fseek(fp, -word2_len, SEEK_CUR);
            fprintf(fp, "%s", word1);
            if (word1_len < word2_len) {
                int i;
                for (i = 0; i < word2_len - word1_len; i++) {
                    fprintf(fp, " ");
                }
            }
        }
    }

    fclose(fp);
    free(temp);  // free the memory allocated for temp buffer
}*/

/*
void replace_word(char *filename, char *word1, char *word2) {
    char temp[100];  // temporary buffer for storing the words to be replaced
    int word1_len = strlen(word1);
    int word2_len = strlen(word2);

    FILE *fp = fopen(filename, "r+");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // replace all occurrences of word1 with word2 and vice versa
    while (fscanf(fp, "%s", temp) == 1) {
        if (strcmp(temp, word1) == 0) {
            fseek(fp, -word1_len, SEEK_CUR);
            fprintf(fp, "%s", word2);
            if (word2_len < word1_len) {
                int i;
                for (i = 0; i < word1_len - word2_len; i++) {
                    fprintf(fp, " ");
                }
            }
        } else if (strcmp(temp, word2) == 0) {
            fseek(fp, -word2_len, SEEK_CUR);
            fprintf(fp, "%s", word1);
            if (word1_len < word2_len) {
                int i;
                for (i = 0; i < word2_len - word1_len; i++) {
                    fprintf(fp, " ");
                }
            }
        }
    }

    fclose(fp);
}
*/


/*
void replace_word(char *filename, char *word1, char *word2) {
    char temp[1000];  // temporary buffer for storing the file contents
    char *p;

    FILE *fp = fopen(filename, "r+");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // read the entire file into the temporary buffer
    fread(temp, 1, 1000, fp);

    // replace all occurrences of word1 with word2 and vice versa
    while ((p = strstr(temp, word1)) != NULL) {
        strncpy(p, word2, strlen(word2));
        memmove(p + strlen(word2), p + strlen(word1), strlen(p + strlen(word1)) + 1);
    }

    while ((p = strstr(temp, word2)) != NULL) {
        strncpy(p, word1, strlen(word1));
        memmove(p + strlen(word1), p + strlen(word2), strlen(p + strlen(word2)) + 1);
    }

    // go back to the beginning of the file and write the modified contents
    rewind(fp);
    fwrite(temp, 1, strlen(temp), fp);
    fclose(fp);
}
*/




/*
void replace_words_in_file(const char* file_path, const char* word1, const char* word2) {
// Открыть файл для чтения и записи
    FILE *file = fopen(file_path, "r+");
    if (file == NULL) {
        fprintf(stderr, "Не удалось открыть файл: %s\n", file_path);
        exit(1);
    }
    char buffer[100]; // Буфер для чтения слова
    size_t offset = 0; // Смещение от начала файла
    size_t word1_len = strlen(word1); // Длина слова1
    size_t word2_len = strlen(word2); // Длина слова2

// Пока не достигнут конец файла
    while (fscanf(file, "%s", buffer) == 1) {
        // Если слово равно слову1, заменяем его на слово2
        if (strcmp(buffer, word1) == 0) {
            fseek(file, offset, SEEK_SET); // Перемещаем указатель на начало слова
            fwrite(word2, sizeof(char), word2_len, file); // Записываем слово2
            if (word2_len < word1_len) { // Если слово2 короче слова1
                for (size_t i = 0; i < word1_len - word2_len; i++) {
                    fputc(' ', file); // Добавляем пробелы для выравнивания
                }
            }
            offset += word2_len; // Увеличиваем смещение на длину слова2
        } else if (strcmp(buffer, word2) == 0) { // Если слово равно слову2, заменяем его на слово1
            fseek(file, offset, SEEK_SET); // Перемещаем указатель на начало слова
            fwrite(word1, sizeof(char), word1_len, file); // Записываем слово1
            if (word1_len < word2_len) { // Если слово1 короче слова2
                for (size_t i = 0; i < word2_len - word1_len; i++) {
                    fputc(' ', file); // Добавляем пробелы для выравнивания
                }
            }
            offset += word1_len; // Увеличиваем смещение на длину слова1
        } else { // Если слово не равно ни слову1, ни слову2, оставляем его без изменений
            offset += strlen(buffer); // Увеличиваем смещение на длину слова
        }
    }

    fclose(file); // Закрываем файл
}
*/



/*
void swap_words_in_file(const char *input_file, const char *output_file, const char *word1, const char *word2) {
    // Открыть входной файл для чтения
    FILE *input = fopen(input_file, "r");
    if (input == NULL) {
        fprintf(stderr, "Не удалось открыть входной файл\n");
        exit(1);
    }

    // Создать выходной файл для записи
    FILE *output = fopen(output_file, "w");
    if (output == NULL) {
        fprintf(stderr, "Не удалось создать выходной файл\n");
        fclose(input);
        exit(1);
    }

    // Считывать файл по словам
    char word[100];
    while (fscanf(input, "%s", word) == 1) {
        // Заменить слова, если они совпадают с заданными
        if (strcmp(word, word1) == 0) {
            strcpy(word, word2);
        } else if (strcmp(word, word2) == 0) {
            strcpy(word, word1);
        }

        // Записать слово в выходной файл
        char c = fgetc(input);
        if (ispunct(c)) {
            fprintf(output, "%s%c", word, c);
        } else {
            fprintf(output, "%s%c", word, ' ');
            ungetc(c, input);
        }
    }

    // Закрыть файлы
    fclose(input);
    fclose(output);
}
*/

/*
void swap_words_in_file(const char *input_file, const char *output_file, const char *word1, const char *word2) {
    // Открыть входной файл для чтения
    FILE *input = fopen(input_file, "r");
    if (input == NULL) {
        fprintf(stderr, "Не удалось открыть входной файл\n");
        exit(1);
    }

    // Создать выходной файл для записи
    FILE *output = fopen(output_file, "w");
    if (output == NULL) {
        fprintf(stderr, "Не удалось создать выходной файл\n");
        fclose(input);
        exit(1);
    }

    // Считывать файл по словам
    char word[100];
    while (fscanf(input, "%s", word) == 1) {
        // Заменить слова, если они совпадают с заданными
        if (strcmp(word, word1) == 0) {
            strcpy(word, word2);
        } else if (strcmp(word, word2) == 0) {
            strcpy(word, word1);
        }

        // Записать слово в выходной файл
        char c = fgetc(input);
        if (ispunct(c)) {
            fprintf(output, "%s%c", word, c);
        } else {
            fprintf(output, "%s%c", word, ' ');
            ungetc(c, input);
        }
    }

    // Закрыть файлы
    fclose(input);
    fclose(output);
}
*/

/*

void swap_words_in_file(const char *input_file, const char *output_file, const char *word1, const char *word2) {
    // Открыть входной файл для чтения
    FILE *input = fopen(input_file, "r");
    if (input == NULL) {
        fprintf(stderr, "Не удалось открыть входной файл\n");
        exit(1);
    }

    // Создать выходной файл для записи
    FILE *output = fopen(output_file, "w");
    if (output == NULL) {
        fprintf(stderr, "Не удалось создать выходной файл\n");
        fclose(input);
        exit(1);
    }

    // Считывать файл по словам
    char word[100];
    while (fscanf(input, "%s", word) == 1) {
        // Заменить слова, если они совпадают с заданными
        if (strcmp(word, word1) == 0) {
            strcpy(word, word2);
        } else if (strcmp(word, word2) == 0) {
            strcpy(word, word1);
        }

        // Записать слово в выходной файл
        fprintf(output, "%s", word);

        // Если слово не является последним в строке, записать пробел
        if (word[strlen(word)-1] != '\n') {
            fprintf(output, " ");
        }
    }

    // Закрыть файлы
    fclose(input);
    fclose(output);
}
*/

/*



void replace_words(const char *filename, const char *old_word, const char *new_word)
{
    // Открываем исходный файл для чтения
    FILE *input_file = fopen(filename, "r");
    if (!input_file) {
        perror("Ошибка при открытии файла");
        return;
    }

    // Открываем новый файл для записи
    char output_filename[strlen(filename) -  4]; // длина имени файла + "_copy"
    sprintf(output_filename, "%s_copy.txt", filename);
    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("Ошибка при создании копии файла");
        fclose(input_file);
        return;
    }

    // Считываем файл по словам и заменяем их
    char word[100]; // предполагаем, что самое длинное слово не больше 100 символов
    while (fscanf(input_file, "%s", word) == 1) {
        if (strcmp(word, old_word) == 0) {
            fputs(new_word, output_file);
        } else if (strcmp(word, new_word) == 0) {
            fputs(old_word, output_file);
        } else {
            fputs(word, output_file);
        }
        fputc(' ', output_file);
    }

    // Закрываем файлы
    fclose(input_file);
    fclose(output_file);
}
*/

////////find_in_file_and_swap(f, word);



/*int replace_words_in_file(const char* filename, const char* first_word, const char* second_word) {
    FILE* file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return 1;
    }
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    // Allocate buffer for file content
    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        printf("Failed to allocate memory for file content.\n");
        fclose(file);
        return 1;
    }
    // Read file content into buffer
    fread(buffer, 1, file_size, file);
    // Replace words in buffer
    char* pos_search = buffer;
    char* pos_replace = NULL;

    while ((pos_search = strstr(pos_search, first_word)) != NULL || (pos_search = strstr(pos_search, second_word)) != NULL) {

        if (pos_search == strstr(buffer, first_word)) {
            // Calculate length difference between search and replace words
            int diff = strlen(second_word) - strlen(first_word);
            // Allocate additional memory if necessary
            if (diff != 0) {
                buffer = (char*)realloc(buffer, file_size + diff + 1); // +1 for the null terminator
                if (buffer == NULL) {
                    printf("Failed to allocate memory for file content.\n");
                    fclose(file);
                    return 1;
                }
                // Update file size and position of replace word in buffer
                file_size += diff;
                pos_replace = buffer + (pos_search - buffer) + strlen(second_word);
                memmove(pos_replace, pos_search + strlen(first_word), strlen(pos_search + strlen(first_word)) + 1);
            } else {
                // Update position of replace word in buffer
                pos_replace = pos_search + strlen(second_word);
            }
            // Copy replace word into buffer
            strncpy(pos_search, second_word, strlen(second_word));
            // Update position of search word in buffer
            pos_search = pos_replace;
        } else {
            // Calculate length difference between search and replace words
            int diff = strlen(first_word) - strlen(second_word);
            // Allocate additional memory if necessary
            if (diff != 0) {
                buffer = (char*)realloc(buffer, file_size + diff + 1); // +1 for the null terminator
                if (buffer == NULL) {
                    printf("Failed to allocate memory for file content.\n");
                    fclose(file);
                    return 1;
                }
                // Update file size and position of replace word in buffer
                file_size += diff;
                pos_replace = buffer + (pos_search - buffer) + strlen(first_word);
                memmove(pos_replace, pos_search + strlen(second_word), strlen(pos_search + strlen(second_word)) + 1);
            } else {
                // Update position of replace word in buffer
                pos_replace = pos_search + strlen(first_word);
            }
            // Copy replace word into buffer
            strncpy(pos_search, second_word, strlen(second_word));
            // Update position of search word in buffer
            pos_search = pos_replace;
        }
    }
    // Write buffer into file
    fseek(file, 0, SEEK_SET);
    fwrite(buffer, 1, file_size, file);
    // Free buffer and close file
    free(buffer);
    fclose(file);
    printf("Words replaced successfully.\n");
    return 0;
}*/


/*int replace_words_in_file(const char* filename, const char* first_word, const char* second_word) {
    FILE* file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return 1;
    }
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    // Allocate buffer for file content
    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        printf("Failed to allocate memory for file content.\n");
        fclose(file);
        return 1;
    }
    // Read file content into buffer
    fread(buffer, 1, file_size, file);
    // Replace words in buffer
    char* pos_search = buffer;
    char* pos_replace = NULL;

    while ((pos_search = strstr(pos_search, first_word)) != NULL || (pos_search = strstr(pos_search, second_word)) != NULL) {

        if (pos_search == strstr(buffer, first_word)) {
            // Calculate length difference between search and replace words
            int diff = strlen(second_word) - strlen(first_word);
            // Allocate additional memory if necessary
            if (diff != 0) {
                buffer = (char*)realloc(buffer, file_size + diff);
                if (buffer == NULL) {
                    printf("Failed to allocate memory for file content.\n");
                    fclose(file);
                    return 1;
                }
                // Update file size and position of replace word in buffer
                file_size += diff;
                pos_replace = buffer + (pos_search - buffer) + strlen(second_word);
                memmove(pos_replace, pos_search + strlen(first_word), strlen(pos_search + strlen(first_word)) + 1);
            } else {
                // Update position of replace word in buffer
                pos_replace = pos_search + strlen(second_word);
            }
            // Copy replace word into buffer
            strncpy(pos_search, second_word, strlen(second_word));
        } else {
            // Calculate length difference between search and replace words
            int diff = strlen(first_word) - strlen(second_word);
            // Allocate additional memory if necessary
            if (diff != 0) {
                buffer = (char*)realloc(buffer, file_size + diff);
                if (buffer == NULL) {
                    printf("Failed to allocate memory for file content.\n");
                    fclose(file);
                    return 1;
                }
                // Update file size and position of replace word in buffer
                file_size += diff;
                pos_replace = buffer + (pos_search - buffer) + strlen(first_word);
                memmove(pos_replace, pos_search + strlen(second_word), strlen(pos_search + strlen(second_word)) + 1);
            } else {
                // Update position of replace word in buffer
                pos_replace = pos_search + strlen(first_word);
            }
            // Copy replace word into buffer
            strncpy(pos_search, first_word, strlen(first_word));
        }
        // Update position of search word in buffer
        pos_search = pos_replace;
    }
    // Write buffer into file
    fseek(file, 0, SEEK_SET);
    fwrite(buffer, 1, file_size, file);
    // Free buffer and close file
    free(buffer);
    fclose(file);
    printf("Words replaced successfully.\n");
    return 0;
}*/

/*int replace_words_in_file(const char* filename, const char* first_word, const char* second_word) {
    FILE* file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return 1;
    }
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    // Allocate buffer for file content
    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        printf("Failed to allocate memory for file content.\n");
        fclose(file);
        return 1;
    }
    // Read file content into buffer
    fread(buffer, 1, file_size, file);
    // Replace words in buffer
    char* pos_search = buffer;
    char* pos_replace = NULL;

    while ((pos_search = strstr(pos_search, first_word)) != NULL || (pos_search = strstr(pos_search, second_word)) != NULL) {

        // Calculate length difference between search and replace words
        int diff = strlen(second_word) - strlen(first_word);
        // Allocate additional memory if necessary
        if (diff != 0) {
            buffer = (char*)realloc(buffer, file_size + diff);
            if (buffer == NULL) {
                printf("Failed to allocate memory for file content.\n");
                fclose(file);
                return 1;
            }
            // Update file size and position of replace word in buffer
            file_size += diff;
            pos_replace = buffer + (pos_search - buffer) + strlen(second_word);
            memmove(pos_replace, pos_search + strlen(first_word), strlen(pos_search + strlen(first_word)) + 1);
        } else {
            // Update position of replace word in buffer
            pos_replace = pos_search + strlen(second_word);
        }
        // Copy replace word into buffer
        strncpy(pos_search, pos_search == strstr(buffer, first_word) ? second_word : first_word, strlen(pos_search == strstr(buffer, first_word) ? first_word : second_word));

        // Update position of search word in buffer
        pos_search = pos_replace;
    }
    // Write buffer into file
    fseek(file, 0, SEEK_SET);
    fwrite(buffer, 1, file_size, file);
    // Free buffer and close file
    free(buffer);
    fclose(file);
    printf("Words replaced successfully.\n");
    return 0;
}*/

/*
int replace_words_in_file(const char* filename, const char* first_word, const char* second_word) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return 1;
    }
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    // Allocate buffer for file content
    char *buffer = (char *) malloc(file_size + 1);
    if (buffer == NULL) {
        printf("Failed to allocate memory for file content.\n");
        fclose(file);
        return 1;
    }
    // Read file content into buffer
    fread(buffer, 1, file_size, file);
    // Replace words in buffer
    char *pos_search = buffer;
    char *pos_replace = NULL;
    while ((pos_search = strstr(pos_search, first_word)) != NULL) {
        // Calculate length difference between search and replace words
        int diff = strlen(second_word) - strlen(first_word);
        // Allocate additional memory if necessary
        if (diff != 0) {
            buffer = (char *) realloc(buffer, file_size + diff + 1);
            if (buffer == NULL) {
                printf("Failed to allocate memory for file content.\n");
                fclose(file);
                return 1;
            }
            // Update file size and position of replace word in buffer
            file_size += diff;
            pos_replace = buffer + (pos_search - buffer) + strlen(second_word);
            memmove(pos_replace, pos_search + strlen(first_word), strlen(pos_search + strlen(first_word)) + 1);
        } else {
            // Update position of replace word in buffer
            pos_replace = pos_search + strlen(second_word);
        }
        // Copy replace word into buffer
        strncpy(pos_search, second_word, strlen(second_word));
        // Update position of search word in buffer
        pos_search = pos_replace;
    }
    // Replace second word with first word in buffer
    pos_search = buffer;
    pos_replace = NULL;
    while ((pos_search = strstr(pos_search, second_word)) != NULL) {
        // Calculate length difference between search and replace words
        int diff = strlen(first_word) - strlen(second_word);
        // Allocate additional memory if necessary
        if (diff != 0) {
            buffer = (char *) realloc(buffer, file_size + diff + 1);
            if (buffer == NULL) {
                printf("Failed to allocate memory for file content.\n");
                fclose(file);
                return 1;
            }
            // Update file size and position of replace word in buffer
            file_size += diff;
            pos_replace = buffer + (pos_search - buffer) + strlen(first_word);
            memmove(pos_replace, pos_search + strlen(second_word), strlen(pos_search + strlen(second_word)) + 1);
        } else {
            // Update position of replace word in buffer
            pos_replace = pos_search + strlen(first_word);
        }
        // Copy replace word into buffer
        strncpy(pos_search, first_word, strlen(first_word));
        // Update position of search word in buffer
        pos_search = pos_replace;
    }
    // Write buffer into file
    fseek(file, 0, SEEK_SET);
    fwrite(buffer, 1, file_size, file);
    // Free buffer and close file
    free(buffer);
    fclose(file);
    printf("Words replaced successfully.\n");
    return 0;
}
*/

/*int replace_words_in_file(const char* filename, const char* first_word, const char* second_word) {
    FILE* file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return 1;
    }
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    // Allocate buffer for file content
    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        printf("Failed to allocate memory for file content.\n");
        fclose(file);
        return 1;
    }
    // Read file content into buffer
    fread(buffer, 1, file_size, file);
    // Replace words in buffer
    char* pos_search = buffer;
    char* pos_replace = NULL;

    while ((pos_search = strstr(pos_search, first_word)) != NULL || (pos_search = strstr(pos_search, second_word)) != NULL) {
        // Calculate length difference between search and replace words
        int diff = strlen(second_word) - strlen(first_word);
        // Allocate additional memory if necessary
        if (diff != 0) {
            buffer = (char*)realloc(buffer, file_size + diff);
            if (buffer == NULL) {
                printf("Failed to allocate memory for file content.\n");
                fclose(file);
                return 1;
            }
            // Update file size and position of replace word in buffer
            file_size += diff;
            pos_replace = buffer + (pos_search - buffer) + strlen(second_word);
            memmove(pos_replace, pos_search + strlen(first_word), strlen(pos_search + strlen(first_word)) + 1);
        } else {
            // Update position of replace word in buffer
            pos_replace = pos_search + strlen(second_word);
        }
        // Copy replace word into buffer
        char* word_to_replace = (pos_search == strstr(buffer, first_word)) ? first_word : second_word;
        strncpy(pos_search, word_to_replace == first_word ? second_word : first_word, strlen(word_to_replace));
        // Update position of search word in buffer
        pos_search = pos_replace;
    }
    // Write buffer into file
    fseek(file, 0, SEEK_SET);
    fwrite(buffer, 1, file_size, file);
    // Free buffer and close file
    free(buffer);
    fclose(file);
    printf("Words replaced successfully.\n");
    return 0;
}*/

/*int replace_words_in_file(const char* filename, const char* first_word, const char* second_word) {
    FILE* file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return 1;
    }
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    // Allocate buffer for file content
    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        printf("Failed to allocate memory for file content.\n");
        fclose(file);
        return 1;
    }
    // Read file content into buffer
    fread(buffer, 1, file_size, file);
    // Replace words in buffer
    char* pos_search = buffer;
    char* pos_replace = NULL;

    while ((pos_search = strstr(pos_search, first_word)) != NULL || (pos_search = strstr(pos_search, second_word)) != NULL) {
        // Determine which word to replace
        const char* word_to_replace = pos_search == strstr(pos_search, first_word) ? first_word : second_word;
        // Calculate length difference between search and replace words
        int diff = strlen(word_to_replace) - strlen(word_to_replace == first_word ? second_word : first_word);
        // Allocate additional memory if necessary
        if (diff != 0) {
            buffer = (char*)realloc(buffer, file_size + diff);
            if (buffer == NULL) {
                printf("Failed to allocate memory for file content.\n");
                fclose(file);
                return 1;
            }
            // Update file size and position of replace word in buffer
            file_size += diff;
            pos_replace = buffer + (pos_search - buffer) + strlen(word_to_replace);
            memmove(pos_replace, pos_search + strlen(word_to_replace), strlen(pos_search + strlen(word_to_replace)) + 1);
        } else {
            // Update position of replace word in buffer
            pos_replace = pos_search + strlen(word_to_replace);
        }
        // Copy replace word into buffer
        strncpy(pos_search, word_to_replace == first_word ? second_word : first_word, strlen(word_to_replace));
        // Update position of search word in buffer
        pos_search = pos_replace;
    }
    // Write buffer into file
    fseek(file, 0, SEEK_SET);
    fwrite(buffer, 1, file_size, file);
    // Free buffer and close file
    free(buffer);
    fclose(file);
    printf("Words replaced successfully.\n");
    return 0;
} */

/*int replace_words_in_file(const char* filename, const char* first_word, const char* second_word) {
    FILE* file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return 1;
    }
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    // Allocate buffer for file content
    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        printf("Failed to allocate memory for file content.\n");
        fclose(file);
        return 1;
    }
    // Read file content into buffer
    fread(buffer, 1, file_size, file);
    // Replace words in buffer
    char* pos_search = buffer;
    char* pos_replace = NULL;

    //while ((pos_search = strstr(pos_search, first_word)) != NULL) {

    while ((pos_search = strstr(pos_search, first_word)) != NULL || (pos_search = strstr(pos_search, second_word)) != NULL) {

        // Calculate length difference between search and replace words
        int diff = strlen(second_word) - strlen(first_word);
        // Allocate additional memory if necessary
        if (diff != 0) {
            buffer = (char*)realloc(buffer, file_size + diff);
            if (buffer == NULL) {
                printf("Failed to allocate memory for file content.\n");
                fclose(file);
                return 1;
            }
            // Update file size and position of replace word in buffer
            file_size += diff;
            pos_replace = buffer + (pos_search - buffer) + strlen(second_word);
            memmove(pos_replace, pos_search + strlen(first_word), strlen(pos_search + strlen(first_word)) + 1);
        } else {
            // Update position of replace word in buffer
            pos_replace = pos_search + strlen(second_word);
        }
        // Copy replace word into buffer

        //strncpy(pos_search, second_word, strlen(second_word));

        if (pos_search == strstr(buffer, first_word)) {
            strncpy(pos_search, second_word, strlen(second_word));
        } else {
            strncpy(pos_search, first_word, strlen(first_word));
        }

        // Update position of search word in buffer
        pos_search = pos_replace;
    }
    // Replace second word with first word in buffer
    pos_search = buffer;
    pos_replace = NULL;
    while ((pos_search = strstr(pos_search, second_word)) != NULL) {
        // Calculate length difference between search and replace words
        int diff = strlen(first_word) - strlen(second_word);
        // Allocate additional memory if necessary
        if (diff != 0) {
            buffer = (char*)realloc(buffer, file_size + diff);
            if (buffer == NULL) {
                printf("Failed to allocate memory for file content.\n");
                fclose(file);
                return 1;
            }
            // Update file size and position of replace word in buffer
            file_size += diff;
            pos_replace = buffer + (pos_search - buffer) + strlen(first_word);
            memmove(pos_replace, pos_search + strlen(second_word), strlen(pos_search + strlen(second_word)) + 1);
        } else {
            // Update position of replace word in buffer
            pos_replace = pos_search + strlen(first_word);
        }
        // Copy replace word into buffer
        strncpy(pos_search, first_word, strlen(first_word));
        // Update position of search word in buffer
        pos_search = pos_replace;
    }
    // Write buffer into file
    fseek(file, 0, SEEK_SET);
    fwrite(buffer, 1, file_size, file);
    // Free buffer and close file
    free(buffer);
    fclose(file);
    printf("Words replaced successfully.\n");
    return 0;
}*/

/*int replace_words_in_file(const char* filename, const char* first_word, const char* second_word) {
    FILE* file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return 1;
    }
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    // Allocate buffer for file content
    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        printf("Failed to allocate memory for file content.\n");
        fclose(file);
        return 1;
    }
    // Read file content into buffer
    fread(buffer, 1, file_size, file);
    // Replace words in buffer
    char* pos_search = buffer;
    char* pos_replace = NULL;
    while ((pos_search = strstr(pos_search, first_word)) != NULL) {
        // Calculate length difference between search and replace words
        int diff = strlen(second_word) - strlen(first_word);
        // Allocate additional memory if necessary
        if (diff != 0) {
            buffer = (char*)realloc(buffer, file_size + diff);
            if (buffer == NULL) {
                printf("Failed to allocate memory for file content.\n");
                fclose(file);
                return 1;
            }
            // Update file size and position of replace word in buffer
            file_size += diff;
            pos_replace = buffer + (pos_search - buffer) + strlen(second_word);
            memmove(pos_replace, pos_search + strlen(first_word), strlen(pos_search + strlen(first_word)) + 1);
        } else {
            // Update position of replace word in buffer
            pos_replace = pos_search + strlen(second_word);
        }
        // Copy replace word into buffer
        strncpy(pos_search, second_word, strlen(second_word));
        // Update position of search word in buffer
        pos_search += strlen(second_word);
    }
    // Write buffer into file
    fseek(file, 0, SEEK_SET);
    fwrite(buffer, 1, file_size, file);
    // Free buffer and close file
    free(buffer);
    fclose(file);
    printf("Words replaced successfully.\n");
    return 0;
}*/

/*
void replace_words_in_file(char *file_name, FILE *lyb, char *first_word, char *second_word) {
    FILE *f;
    FILE *compressed_file;
    char *word_tmp;
    char *cleaned_word;
    word_tmp = (char*) malloc(50 * sizeof (char));
    if (fopen_s(&f, file_name, "r+t") != 0) {
        printf("Failed to open input file.\n");
        return;
    }
    while(fscanf(f, "%s", word_tmp) == 1) {
        cleaned_word = dell_punct_marks(word_tmp);
        //printf("%s ", cleaned_word);
        if (strcmp(first_word, cleaned_word) == 0) {
            fputs(second_word, compressed_file);
            fputs(" ", compressed_file);
        } else if (strcmp(second_word, cleaned_word) == 0) {
            fputs(first_word, compressed_file);
            fputs(" ", compressed_file);
        } else if(check_in_lyb(lyb, cleaned_word) == 0){
            fputs(word_tmp, compressed_file);
            fputs(" ", compressed_file);
        }
    }
    free(word_tmp);
    fclose(compressed_file);
    fclose(f);
}
*/

/*int replace_words_in_file(const char* filename, const char* search_word, const char* replace_word) {
    FILE* file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return 1;
    }
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    // Allocate buffer for file content
    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        printf("Failed to allocate memory for file content.\n");
        fclose(file);
        return 1;
    }
    // Read file content into buffer
    fread(buffer, 1, file_size, file);
    // Replace words in buffer
    char* pos_search = strstr(buffer, search_word);
    char* pos_replace = strstr(buffer, replace_word);
    while (pos_search != NULL || pos_replace != NULL) {
        // Check which word is found first
        if (pos_search != NULL && (pos_replace == NULL || pos_search < pos_replace)) {
            // Calculate length difference between search and replace words
            int diff = strlen(replace_word) - strlen(search_word);
            // Shift remaining characters to right if necessary
            if (diff > 0) {
                memmove(pos_search + strlen(replace_word), pos_search + strlen(search_word), strlen(pos_search + strlen(search_word)) + 1);
            } else if (diff < 0) {
                memmove(pos_search + strlen(replace_word), pos_search + strlen(search_word) - diff, strlen(pos_search + strlen(search_word)) + 1);
            }
            // Copy replace word into buffer
            strncpy(pos_search, replace_word, strlen(replace_word));
            // Search for next occurrence of search word
            pos_search = strstr(pos_search + strlen(replace_word), search_word);
            // Update position of replace word in buffer
            pos_replace = strstr(pos_search, replace_word);
        } else {
            // Calculate length difference between search and replace words
            int diff = strlen(search_word) - strlen(replace_word);
            // Shift remaining characters to right if necessary
            if (diff > 0) {
                memmove(pos_replace + strlen(search_word), pos_replace + strlen(replace_word), strlen(pos_replace + strlen(replace_word)) + 1);
            } else if (diff < 0) {
                memmove(pos_replace + strlen(search_word) - diff, pos_replace + strlen(replace_word), strlen(pos_replace + strlen(replace_word)) + 1);
            }
            // Copy search word into buffer
            strncpy(pos_replace, search_word, strlen(search_word));
            // Search for next occurrence of replace word
            pos_replace = strstr(pos_replace + strlen(search_word), replace_word);
            // Update position of search word in buffer
            pos_search = strstr(pos_replace, search_word);
        }
    }
    // Write buffer into file
    fseek(file, 0, SEEK_SET);
    fwrite(buffer, 1, strlen(buffer), file);
    // Free buffer and close file
    free(buffer);
    fclose(file);
    printf("Words replaced successfully.\n");
    return 0;
}*/

/*
void replace_word(char *file_name, const char *replace_word, const char *search_word)
{
    FILE* file = fopen(file_name, "r+");
    long file_size;
    char* buffer;
    char* pos;
    int diff;
    if (file == NULL) {
        printf("Failed to open file: %s\n", file_name);
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_SET);

    file_size = ftell(file);
    buffer = (char*)malloc(file_size + 1);

    fseek(file, 0, SEEK_SET);
    if (buffer == NULL) {
        printf("Failed to allocate memory for file content.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, file_size, file);

    pos = strstr(buffer, search_word);

    char* temp_word = (char*)malloc(strlen(search_word) + 1);

    while (pos != NULL) {
        // Calculate length difference between search and replace words
        diff = strlen(replace_word) - strlen(search_word);
        // Shift remaining characters to right or left depending on difference between lengths
        if (diff > 0) {
            memmove(pos + strlen(replace_word), pos + strlen(search_word), strlen(pos + strlen(search_word)) + 1);
        } else if (diff < 0) {
            memmove(pos + strlen(replace_word), pos + strlen(search_word) + diff, strlen(pos + strlen(search_word) + diff) + 1);
        }
        // Copy replace word into buffer
        if (strlen(replace_word) <= strlen(search_word)) {
            strncpy(pos, replace_word, strlen(replace_word));
        } else {
            strncat(pos, replace_word + strlen(search_word), strlen(replace_word) - strlen(search_word));
        }
        // Search for next occurrence of search word
        pos = strstr(pos + strlen(replace_word), search_word);
    }
    fseek(file, 0, SEEK_SET);
    fwrite(buffer, 1, strlen(buffer), file);
    // Free buffer and close file
    free(buffer);
    fclose(file);
}
*/

/*    FILE* file = fopen(file_name, "r+");
    if (file == NULL) {
        printf("Failed to open file: %s\n", file_name);
        exit(EXIT_FAILURE);
    }
    long file_size;
    fseek(file, 0, SEEK_SET);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        printf("Failed to allocate memory for file content.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    fread(buffer, 1, file_size, file);
    char* pos = strstr(buffer, search_word);
    while (pos != NULL) {
        // Calculate length difference between search and replace words
        int diff = strlen(replace_word) - strlen(search_word);
        // Shift remaining characters to right or left depending on difference between lengths
        if (diff > 0) {
            memmove(pos + strlen(replace_word), pos + strlen(search_word), strlen(pos + strlen(search_word)) + 1);
        } else if (diff < 0) {
            memmove(pos + strlen(replace_word), pos + strlen(search_word) + diff, strlen(pos + strlen(search_word) + diff) + 1);
        }
        // Copy replace word into buffer
        if (strlen(replace_word) <= strlen(search_word)) {
            strncpy(pos, replace_word, strlen(replace_word));
        } else {
            strncat(pos, replace_word + strlen(search_word), strlen(replace_word) - strlen(search_word));
        }
        // Search for next occurrence of search word
        pos = strstr(pos + strlen(replace_word), search_word);
    }
    fseek(file, 0, SEEK_SET);
    fwrite(buffer, 1, strlen(buffer), file);
    // Free buffer and close file
    free(buffer);
    fclose(file);*/