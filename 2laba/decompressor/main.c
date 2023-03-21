#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <Windows.h>
#include <fcntl.h>
#define MAX_WORD_LEN 50

typedef struct{
    char *word1;
    char *word2;
}replacement_words;

typedef struct{
    replacement_words *words;
    int num_of_words;
}Library;

char* dell_punct_marks(char *word_ptr);
void find_key(FILE *file, char *key);
void replace_word(char* text, const char* old_word, const char* new_word);
void save_control_characters(FILE* file, FILE* file1);
void decompress_file(const char *input_file, const char* output_file, const Library *lyb);

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    char file_name[110] = "C://Users//Alexander//Documents//GitHub//Sergei-Pirat-2009-mp3//2laba//cmake-build-debug//compressed_file.txt";
    char key[26] = "!1RvD8*ku$%TqFw&zPbN@5sLx";
    FILE *file;
    file = fopen(file_name, "r");

    if(file == NULL)
    {
        printf("Ti poputal menchik");
        exit(EXIT_FAILURE);
    }


    find_key(file, key);
    char word[MAX_WORD_LEN];
    printf("%d", ftell(file));
    fscanf(file, "%s", word);
    printf("%s", word);

    return 0;
}

void delete_lyb(FILE *file, char *key)
{
    if(file == NULL)
        return;

   // ftruncate(fd, );
}

void find_key(FILE *file, char *key)
{
    if(file == NULL)
        exit(EXIT_FAILURE);
    char word[MAX_WORD_LEN];
    while(fscanf(file, "%s", word) == 1)
    {
        if(strcmp(word, key) == 0)
        {
            return;
        }
    }
}

char* dell_punct_marks(char *word_ptr) {
    if (word_ptr == NULL || *word_ptr == '\0') {
        return NULL;
    }
    char *word = word_ptr;
    size_t size = strlen(word);
    while (size > 0 && !isalpha(word[0])) {
        memmove(word, word + 1, size--);
    }
    while (size > 0 && !isalpha(word[size - 1])) {
        word[--size] = '\0';
    }

    return word;
}

void decompress_file(const char *input_file, const char* output_file, const Library *lyb)
{
    FILE *fr;

    fr = fopen(input_file, "rt");
    if(fr == NULL)
        return;

    FILE *fw;

    fw = fopen(output_file, "wt");
    if(fw == NULL)
        return;

    char word[MAX_WORD_LEN];
    char tmp_word[MAX_WORD_LEN];
    char *cleaned_word;
    char next_chars[10];
    int flag = 1;


    while(fscanf(fr, "%s", word) == 1)
    {
        strcpy(tmp_word, word);
        //next_char = (char)getc(fr);
        cleaned_word = dell_punct_marks(word);
        flag = 1;
        for (int i = 0; i < lyb->num_of_words - 1; ++i) {
            if(strcmp(cleaned_word, lyb->words[i].word1) == 0) {
                replace_word(tmp_word, cleaned_word, lyb->words[i].word2);
                fputs(tmp_word, fw);
                save_control_characters(fw, fr);
                flag = 0;
            } else if(strcmp(cleaned_word, lyb->words[i].word2) == 0) {
                replace_word(tmp_word, cleaned_word, lyb->words[i].word1);
                fputs(tmp_word, fw);
                save_control_characters(fw, fr);
                flag = 0;
            }
        } if (flag == 1) {
            fputs(tmp_word, fw);
            save_control_characters(fw, fr);
        }

    }
    //free(cleaned_word);
    fclose(fr);
    fclose(fw);
}

void save_control_characters(FILE* file, FILE* file1) {
    int next_char = fgetc(file1);
    while(next_char == ' ' || next_char == '\n' || next_char == '\t' || next_char == '\r' || next_char == '\v' || next_char == '\f') {
        fputc(next_char, file);
        next_char = fgetc(file1);
    }
    if(next_char != EOF)
        fseek(file1, -1, SEEK_CUR);
}

void replace_word(char* text, const char* old_word, const char* new_word) {
    char* pos = text;
    int old_len = strlen(old_word);
    int new_len = strlen(new_word);

    while ((pos = strstr(pos, old_word)) != NULL) {
        memmove(pos + new_len, pos + old_len, strlen(pos + old_len) + 1);
        memcpy(pos, new_word, new_len);
        pos += new_len;
    }
}
